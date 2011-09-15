#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "memprof/sample.h"
#include "StackTrace.h"
#include "memprof/server.h"
#include <QTimer>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), aboutDialog(new AboutDialog(this)), server(new memprof::server), dirty(false), frame(0), poolAllocationValues(7)
{
    ui->setupUi(this);
    ui->poolStatisticsWidget->resizeColumnsToContents();

    connect(ui->actionAbout, SIGNAL(activated()),
                     this, SLOT(openAboutDialog()));

    const QPushButton* button = ui->buttonBox->button(QDialogButtonBox::Reset);

    connect(button, SIGNAL(clicked(bool)), this, SLOT(onResetData()));

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(rebuildViews()));
    timer->start(100);

    server->register_listener(this);
    serverThread = new ServerThread(server);
    serverThread->start();

    setWindowState(Qt::WindowMaximized);
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
    QMutexLocker locker(&mutex);
    ++frame;
}

void MainWindow::on_allocation(const memprof::sample& sample)
{
    QMutexLocker locker(&mutex);
    update(sample);
    updatePoolStatistics(sample);
    dirty = true;
}

void MainWindow::onResetData()
{
    QMutexLocker locker(&mutex);
    rootNodes.clear();
    poolAllocations.clear();
    frame = 0;
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

void MainWindow::updatePoolStatistics(const memprof::sample& sample)
{
    const size_t id = sample.getPoolID();
    const size_t size = sample.getAllocatedBytes();

    if(poolAllocations.find(id) == poolAllocations.end())
    {
        boost::shared_array<size_t> values(new size_t[poolAllocationValues]);
        for(int i = 0; i < poolAllocationValues; ++i)
        {
            values[i] = 0;
        }

        values[2] = size;

        poolAllocations[id] = values;
    }

    ++poolAllocations[id][0];

    poolAllocations[id][1] += size;

    poolAllocations[id][2] = std::min(poolAllocations[id][2], size);
    poolAllocations[id][3] = std::max(poolAllocations[id][3], size);
    poolAllocations[id][4] = static_cast<double>(poolAllocations[id][1]) / static_cast<double>(poolAllocations[id][0]);
    poolAllocations[id][5] = static_cast<double>(poolAllocations[id][0]) / static_cast<double>(frame);
    poolAllocations[id][6] = static_cast<double>(poolAllocations[id][1]) / static_cast<double>(frame);
}

void MainWindow::rebuildViews()
{
    if(!dirty) return;

    rebuildLiveView();
    rebuildPoolStatisticsView();

    dirty = false;
}

void MainWindow::rebuildLiveView()
{
    QTreeWidget* liveView = ui->liveView;

    QTreeWidgetItem* top;

    QMutexLocker locker(&mutex);

    while((top = liveView->takeTopLevelItem(0)) != 0);

    QList<QTreeWidgetItem*> items;

    for(auto i = rootNodes.begin(); i != rootNodes.end(); ++i)
    {
        items.append(createItem(i->second));
    }

    liveView->addTopLevelItems(items);

    liveView->expandAll();

    liveView->setColumnWidth(0, 700);

    for(int i = 1; i < liveView->columnCount(); ++i)
    {
        liveView->resizeColumnToContents(i);
    }
}

void MainWindow::rebuildPoolStatisticsView()
{
    QTableWidget* table = ui->poolStatisticsWidget;

    QMutexLocker locker(&mutex);

    int rowCount = table->rowCount();

    while(rowCount > 0)
    {
        table->removeRow(0);
        rowCount = table->rowCount();
    }

    int row = 0;
    for(auto i = poolAllocations.begin(); i != poolAllocations.end(); ++i)
    {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString("Pool %1").arg(i->first)));

        for(int j = 0; j < poolAllocationValues; ++j)
        {
            table->setItem(row, j + 1, new QTableWidgetItem(QString("%1").arg(i->second[j])));
        }

        ++row;
    }

    table->resizeColumnsToContents();
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
