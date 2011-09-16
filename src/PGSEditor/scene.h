#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = 0);

signals:

public slots:

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);

    void setStates();
};

#endif // SCENE_H
