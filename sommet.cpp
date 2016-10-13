#include "sommet.h"

Sommet::Sommet()
{

}
Sommet::Sommet(QVector3D point){
    this->point=point;
    this->face=NULL;
}

Face* Sommet::getFace(){
    return face;
}
void Sommet::setFace(Face* face){
    if(!face){
        this->face=face;
    }
}
QVector3D Sommet::getPoint() const{
    return point;
}
bool Sommet::operator!=(Sommet const& a) const{
    return a.getPoint()!=this->getPoint();
}
