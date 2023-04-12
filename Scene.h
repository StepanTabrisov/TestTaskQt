#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPainter>
#include <QPainterPath>
#include <QPointF>
#include <math.h>
#include <Road.h>

class Scene: public QGraphicsScene {
    Q_OBJECT
public:
    Scene(QObject* parent);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void DrawRoads(QVector<Road>& roads);
    void FindDistance(QVector<Road>& roads, QPointF &point);
    void FindMinDistanceCoord(QVector<Road> &roads, QPointF &point);
    void SetRoads(QVector<Road>& roads);

    double CalculateDistToLine(QPointF start, QPointF end, QPointF& point);
    double CalculateDistToCoord(QPointF linePoint, QPointF& point);
    QPointF FindPoint(QPointF start, QPointF end, QPointF point);
    bool CheckPoint(QPointF start, QPointF end, QPointF point);

    void DrawLine(QPointF start, QPointF end);

private:
    QVector<Road> roads;
    int countClick;
};

#endif // SCENE_H
