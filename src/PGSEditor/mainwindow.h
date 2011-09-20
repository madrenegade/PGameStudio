#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class Controller;
class SceneDockWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onSceneChanged();

    void onSetSingleView();
    void onSetMultiView();

private:
    Ui::MainWindow *ui;

    Controller* controller;

    QWidget* viewWidget;

    SceneDockWidget* sceneDock;
};

#endif // MAINWINDOW_H
