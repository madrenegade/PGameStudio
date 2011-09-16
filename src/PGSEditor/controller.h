#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "mainwindow.h"
#include "newscenewizard.h"

#include <boost/scoped_ptr.hpp>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(MainWindow* mainWindow);

signals:

public slots:
    void onNewScene();

private:
    MainWindow* mainWindow;

    boost::scoped_ptr<NewSceneWizard> newSceneWizard;
};

#endif // CONTROLLER_H
