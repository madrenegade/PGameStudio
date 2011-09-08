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

void MainWindow::on_new_frame()
{
    std::cout << "on_new_frame" << std::endl;
    QMutexLocker locker(&mutex);
    ++frame;
    std::cout << "on_new_frame2" << std::endl;
}

void MainWindow::on_allocation(const memprof::sample& sample)
{
    std::cout << "on_allocation" << std::endl;
    QString frameMessages;

    const std::list<StackFrame>& frames = sample.getStackTrace().getFrames();

    unsigned int currentFrame = 1;

    for(std::list<StackFrame>::const_iterator i = frames.begin(); i != frames.end(); ++i)
    {
        frameMessages.append(QString("%1: %2\n").arg(currentFrame).arg(QString::fromStdString(i->getFunction())));
        ++currentFrame;
    }

    QMutexLocker locker(&mutex);
    //ui->rawDataTextBrowser->append(QString("ALLOCATION_BEGIN\nSize: %1 bytes\n%2ALLOCATION_END\n").arg(sample.getAllocatedBytes()).arg(frameMessages));
    update(sample);
    dirty = true;
    std::cout << "on_allocation2" << std::endl;
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

    liveView->resizeColumnToContents(0);

    dirty = false;
}

QTreeWidgetItem* MainWindow::createItem(const SampleNode& node)
{
    QStringList columns;
    columns.append(QString::fromStdString(node.getName()));
    columns.append(QString("%1").arg(node.getNumAllocations()));
    columns.append(QString("%1").arg(node.getNumSelfAllocations()));
    columns.append(QString("%1").arg(node.getTotalSize()));
    columns.append(QString("%1").arg(node.getSelfSize()));
    columns.append(QString("%1").arg(node.getNumAllocationsPerFrame()));
    columns.append(QString("%1").arg(node.getNumSelfAllocationsPerFrame()));
    columns.append(QString("%1").arg(node.getTotalSizePerFrame()));
    columns.append(QString("%1").arg(node.getSelfSizePerFrame()));

    QTreeWidgetItem* item = new QTreeWidgetItem((QTreeWidget*) 0, columns);

    for(SampleNode::Children::const_iterator i = node.getChildren().begin(); i != node.getChildren().end(); ++i)
    {
        item->addChild(createItem(i->second));
    }

    return item;
}
