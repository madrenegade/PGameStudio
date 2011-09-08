#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "memprof/sample.h"
#include "StackTrace.h"
#include "memprof/server.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), aboutDialog(new AboutDialog(this)), server(new memprof::server), dirty(false), frame(0)
{
    ui->setupUi(this);

    connect(ui->actionAbout, SIGNAL(activated()),
                     this, SLOT(openAboutDialog()));

    connect(this, SIGNAL(rawDataArrived(const QString&)), this, SLOT(onRawDataArrived(const QString&)));

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(rebuildLiveView()));
    timer->start(100);

    server->register_listener(this);
    serverThread = new ServerThread(server);
    serverThread->start();
}

MainWindow::~MainWindow()
{
    serverThread->wait(1000);
    serverThread->exit(1);

    delete server;

    delete serverThread;
    delete ui;
}

void MainWindow::onRawDataArrived(const QString &data)
{
    ui->rawDataTextBrowser->append(data);
}

void MainWindow::on_new_frame()
{
    QMutexLocker locker(&mutex);
    ++frame;
}

void MainWindow::on_allocation(const memprof::sample& sample)
{
    QString frameMessages;

    const std::list<StackFrame>& frames = sample.getStackTrace().getFrames();

    unsigned int currentFrame = 1;

    for(std::list<StackFrame>::const_iterator i = frames.begin(); i != frames.end(); ++i)
    {
        frameMessages.append(QString("%1: %2\n").arg(currentFrame).arg(QString::fromStdString(i->getFunction())));
        ++currentFrame;
    }

    QMutexLocker locker(&mutex);
    rawDataArrived(QString("ALLOCATION_BEGIN\nSize: %1 bytes\n%2ALLOCATION_END\n").arg(sample.getAllocatedBytes()).arg(frameMessages));
    update(sample);
    dirty = true;
}

void MainWindow::openAboutDialog() const
{
    aboutDialog->show();
}

void MainWindow::update(const memprof::sample& sample)
{
    std::string function = sample.getStackTrace().getFrames().front().getFunction();

    if(rootNodes.find(function) == rootNodes.end())
    {
        rootNodes[function] = SampleNode(function);
    }

    rootNodes[function].add(sample, frame);
}

void MainWindow::rebuildLiveView()
{
    if(!dirty) return;

    QTreeWidget* liveView = ui->liveView;

    QTreeWidgetItem* top;

    QMutexLocker locker(&mutex);

    while((top = liveView->takeTopLevelItem(0)) != 0);

    QList<QTreeWidgetItem*> items;

    for(NodeMap::const_iterator i = rootNodes.begin(); i != rootNodes.end(); ++i)
    {
        items.append(createItem(i->second));
    }

    liveView->addTopLevelItems(items);

    liveView->expandAll();

    for(int i = 0; i < liveView->columnCount(); ++i)
    {
        liveView->resizeColumnToContents(i);
    }

    dirty = false;
}

QTreeWidgetItem* MainWindow::createItem(const SampleNode& node)
{
    const double div = 1024.0;
    QString unit("KByte");

    double totalSize = static_cast<double>(node.getTotalSize()) / div;
    double selfSize = static_cast<double>(node.getSelfSize()) / div;
    double totalSizePerFrame = static_cast<double>(node.getTotalSizePerFrame()) / div;
    double selfSizePerFrame = static_cast<double>(node.getSelfSizePerFrame()) / div;

    QStringList columns;
    columns.append(QString::fromStdString(node.getName()));
    columns.append(QString("%1").arg(node.getNumAllocations()));
    columns.append(QString("%1").arg(node.getNumSelfAllocations()));
    columns.append(QString("%1 %2").arg(totalSize).arg(unit));
    columns.append(QString("%1 %2").arg(selfSize).arg(unit));
    columns.append(QString("%1").arg(node.getNumAllocationsPerFrame()));
    columns.append(QString("%1").arg(node.getNumSelfAllocationsPerFrame()));
    columns.append(QString("%1 %2").arg(totalSizePerFrame).arg(unit));
    columns.append(QString("%1 %2").arg(selfSizePerFrame).arg(unit));

    QTreeWidgetItem* item = new QTreeWidgetItem((QTreeWidget*) 0, columns);

    for(int i = 1; i < item->columnCount(); ++i)
    {
        item->setTextAlignment(i, Qt::AlignRight);
    }

    for(SampleNode::Children::const_iterator i = node.getChildren().begin(); i != node.getChildren().end(); ++i)
    {
        item->addChild(createItem(i->second));
    }

    return item;
}
