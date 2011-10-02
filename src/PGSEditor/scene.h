#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class EditorApplication;

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(EditorApplication* app, QObject *parent = 0);

signals:

public slots:

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);

    void setStates();

private:
    EditorApplication* app;
};

#endif // SCENE_H
