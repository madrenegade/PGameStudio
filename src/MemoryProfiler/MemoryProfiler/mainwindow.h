#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMutex>
#include <QTreeWidgetItem>

#include "samplenode.h"
#include "aboutdialog.h"
#include "serverthread.h"
#include "memprof/change_listener.h"

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
    void rebuildLiveView();

private:
    void update(const memprof::sample& sample);

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
};

#endif // MAINWINDOW_H
