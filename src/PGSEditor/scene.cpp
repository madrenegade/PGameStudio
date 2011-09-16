#include "scene.h"

#include <QPainter>
#include <QTimer>

#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

Scene::Scene(QObject *parent) :
    QGraphicsScene(parent)
{
//    auto timer = new QTimer(this);
//    timer->setInterval(1000);
//    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
//    timer->start();
}

void Scene::drawBackground(QPainter *painter, const QRectF &rect)
{
    float width = float(painter->device()->width());
    float height = float(painter->device()->height());

    painter->beginNativePainting();
    setStates();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(60.0, width / height, 0.01, 15.0);

    glMatrixMode(GL_MODELVIEW);

    painter->endNativePainting();
}

void Scene::setStates()
{
    glClearColor(0, 0, 0, 1.0);

//     glEnable(GL_DEPTH_TEST);
//     glEnable(GL_CULL_FACE);

     glMatrixMode(GL_PROJECTION);
     glPushMatrix();
     glLoadIdentity();

     glMatrixMode(GL_MODELVIEW);
     glPushMatrix();
     glLoadIdentity();
}
