#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "aboutdialog.h"
#include "serverthread.h"

namespace Ui {
    class MainWindow;
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

    ServerThread* serverThread;
};

#endif // MAINWINDOW_H
