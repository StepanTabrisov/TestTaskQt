#include <Scene.h>

Scene::Scene(QObject* parent) : QGraphicsScene(parent)
{
    countClick = 0;
}

void Scene::SetRoads(QVector<Road> &roads){
    this->roads = roads;
}

void Scene::DrawRoads(QVector<Road>& roads){
    QPainterPath path;
    for(int i = 0; i < roads.size(); i++){
        for(int j = 0; j < roads[i].GetSize(); j++){
            if(j==0){
                path.moveTo(roads[i].GetPoint(j));
            } else{
                path.lineTo(roads[i].GetPoint(j));
            }
        }
    }
    this->addPath(path);
}

void Scene::DrawLine(QPointF start, QPointF end){
    this->addLine(start.x(), start.y(), end.x(), end.y(), QPen(Qt::darkRed, 3));
}

/*
1. поиск дороги (перебор расстояний до координат, нахождение минимального, сохраниение индекса дороги)
2. поиск кратчайшего пути(перебор расстояний до прямых если меньше чем до координат то рисовать + поиск координат)
----------------------------------

1. поиск расстояния до двух координат, поиск расстояния до прямой этих координат, выбор наименьшего
    если наименьший путь до координаты до отрисовка,
        иначе поиск координат, отрисовка

*/

// расстояние до отрезка
double Scene::CalculateDistToLine(QPointF start, QPointF end, QPointF& point){
     double dist = 0.0;

     dist = abs((end.y() - start.y()) * point.x() - (end.x() - start.x()) * point.y() + end.x() * start.y() - end.y() * start.x()) /
             sqrt(pow(end.y() - start.y(), 2) + pow(end.x() - start.x(), 2));

     return dist;
}

// расстояние до координаты дороги
double Scene::CalculateDistToCoord(QPointF linePoint, QPointF& point){
     double dist = 0.0;

     dist = sqrt(pow(point.x() - linePoint.x(), 2) + pow(point.y() - linePoint.y(), 2));

     return dist;
}

// поиск координаты перпендируляра
QPointF Scene::FindPoint(QPointF start, QPointF end, QPointF point){
    QPointF temp;

    double x = 0.0;
    double y = 0.0;

    x = ((end.x() - start.x()) * (end.y() - start.y()) * (point.y() - start.y()) + start.x() * pow(end.y() - start.y(), 2)
         + point.x() * pow(end.x() - start.x(), 2)) / (pow(end.y() - start.y(), 2) + pow(end.x() - start.x(), 2));
    y=(end.y() - start.y()) * (x - start.x()) / (end.x() - start.x()) + start.y();

    temp.setX(x);
    temp.setY(y);

    return temp;
}

double GetMinDist(double dist1, double dist2){
    return dist1 < dist2 ? dist1 : dist2;
}

// проверка координты перпендикуляра
bool Scene::CheckPoint(QPointF start, QPointF end, QPointF point){
    double left = (point.x() - start.x()) / (end.x() - start.x());
    double right = (point.y() - start.y()) / (end.y() - start.y());

    if(left == right && start.x() < point.x() && point.x() < end.x() && start.y() < point.y() && point.y() < end.y()) return true;
    return false;
}

// поиск кратчайшего расстояния до прямой
void Scene::FindDistance(QVector<Road> &roads, QPointF &point){
    double minDist = 65000.0;

    double startDist = 0.0;
    double endDist = 0.0;
    double midDist = 0.0;
    QPointF tempPoint;

    for(int i = 0; i < roads.size(); i++){
        for(int j = 0; j < roads[i].GetSize(); j++){

            if(j == roads[i].GetSize() - 1){
                break;
            }

            startDist = CalculateDistToCoord(roads[i].GetPoint(j), point);
            endDist = CalculateDistToCoord(roads[i].GetPoint(j + 1), point);
            midDist = CalculateDistToLine(roads[i].GetPoint(j), roads[i].GetPoint(j + 1), point);

            if(midDist < startDist && midDist < endDist && midDist < minDist ){
                tempPoint = FindPoint(roads[i].GetPoint(j), roads[i].GetPoint(j + 1), point);
                if(CheckPoint(roads[i].GetPoint(j), roads[i].GetPoint(j + 1), tempPoint)){
                    minDist = midDist;
                }
            }

            if(startDist < minDist){
                minDist = startDist;
                tempPoint = roads[i].GetPoint(j);
            }

            if(endDist < minDist) {
                minDist = endDist;
                tempPoint = roads[i].GetPoint(j + 1);
            }
        }
    }

    this->DrawLine(point, tempPoint);
}


// поиск кратчайшего расстояния до координат дорог
void Scene::FindMinDistanceCoord(QVector<Road> &roads, QPointF &point){
    double minDist = 65000.0;
    double tempDist = 0.0;
    QPointF temp;
    for(int i = 0; i < roads.size(); i++){
        for(int j = 0; j < roads[i].GetSize(); j++){
            tempDist = this->CalculateDistToCoord(roads[i].GetPoint(j), point);
            if (tempDist < minDist){
                minDist = tempDist;
                temp = roads[i].GetPoint(j);
            }
        }
    }
    this->DrawLine(point, temp);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event){
   double sizePoint = 5;
   QPointF startPoint, endPoint;
   if(event->button() == Qt::LeftButton){
       countClick++;
       switch (countClick) {
            case 1:
                startPoint = event->scenePos();
                this->addEllipse(startPoint.x(), startPoint.y(), sizePoint, sizePoint, QPen(Qt::green), QBrush(Qt::green));
                this->FindMinDistanceCoord(this->roads, startPoint);
                //this->FindDistance(this->roads, startPoint);
                break;

            case 2:
                endPoint = event->scenePos();
                this->addEllipse(endPoint.x(), endPoint.y(), sizePoint, sizePoint, QPen(Qt::red), QBrush(Qt::red));
                this->FindMinDistanceCoord(this->roads, endPoint);
                //this->FindDistance(this->roads, endPoint);
                countClick = 0;
                break;

            default:
                break;
       }
   }else{
       qDebug() << "Right" << Qt::endl;

   }
}
