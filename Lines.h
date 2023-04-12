#ifndef LINES_H
#define LINES_H

#include <QPointF>

class Line
{
public:
    Line();
    Line(QPointF start, QPointF end);
    QPointF start;
    QPointF end;
};

#endif // LINES_H
