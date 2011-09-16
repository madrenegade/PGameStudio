#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class Controller;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onSceneChanged();
    void onAssetImported();

    void onSetSingleView();
    void onSetMultiView();

private:
    Ui::MainWindow *ui;

    Controller* controller;

    QWidget* viewWidget;
};

#endif // MAINWINDOW_H
