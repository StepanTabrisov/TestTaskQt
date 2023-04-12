#ifndef ROAD_H
#define ROAD_H

#include <QVector>
#include <QPoint>

class Road {
public:
    Road();
    QPointF GetPoint(int index);
    void AddPoint(QPointF& point);
    int GetSize();
private:
    QVector<QPointF> points;
};

#endif // ROAD_H
