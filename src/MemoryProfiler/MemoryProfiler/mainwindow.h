#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "aboutdialog.h"
#include "serverthread.h"

namespace Ui {
    class MainWindow;
}

namespace memprof {
    class server;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void openAboutDialog() const;

private:
    Ui::MainWindow *ui;

    AboutDialog* aboutDialog;

    memprof::server* server;
    ServerThread* serverThread;
};

#endif // MAINWINDOW_H
