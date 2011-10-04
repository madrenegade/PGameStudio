#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGLWidget>

namespace Ui {
    class MainWindow;
}

class Controller;
class SceneDockWidget;
class SingleViewWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QGLWidget* getGLWidget();

public slots:
    void onSceneChanged();

    void onSetSingleView();
    void onSetMultiView();

private:
    Ui::MainWindow *ui;

    Controller* controller;

    SingleViewWidget* viewWidget;

    SceneDockWidget* sceneDock;
};

#endif // MAINWINDOW_H
