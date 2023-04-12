#include <Road.h>

Road::Road(){

}

void Road::AddPoint(QPointF& point){
    points.push_back(point);
}

int Road::GetSize(){
    return points.size();
}

QPointF Road::GetPoint(int index){
    return points[index];
}
