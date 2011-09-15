#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMutex>
#include <QTreeWidgetItem>

#include "samplenode.h"
#include "aboutdialog.h"
#include "serverthread.h"
#include "memprof/change_listener.h"

#include <boost/shared_array.hpp>

namespace Ui {
    class MainWindow;
}

namespace memprof {
    class server;
    class sample;
}

class MainWindow : public QMainWindow, public memprof::change_listener
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    virtual void on_new_frame();
    virtual void on_allocation(const memprof::sample& sample);

public slots:
    void openAboutDialog() const;

    void rebuildViews();

    void onResetData();

private:
    void update(const memprof::sample& sample);
    void updatePoolStatistics(const memprof::sample& sample);

    void rebuildLiveView();
    void rebuildPoolStatisticsView();

    QTreeWidgetItem* createItem(const SampleNode& node);

    Ui::MainWindow *ui;
    AboutDialog* aboutDialog;

    memprof::server* server;
    ServerThread* serverThread;

    mutable QMutex mutex;

    bool dirty;
    size_t frame;

    typedef std::map<std::string, SampleNode> NodeMap;
    NodeMap rootNodes;

    // values[0] - numAllocations
    // values[1] - totalAllocSize
    // values[2] - minAllocSize
    // values[3] - maxAllocSize
    // values[4] - avgAllocSize
    // values[5] - numAllocsPerFrame
    // values[6] - allocSizePerFrame
    const size_t poolAllocationValues;

    typedef std::map<size_t, boost::shared_array<size_t> > PoolMap;
    PoolMap poolAllocations;
};

#endif // MAINWINDOW_H
