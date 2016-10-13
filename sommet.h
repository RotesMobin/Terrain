#ifndef SOMMET_H
#define SOMMET_H

#include <QObject>
#include <face.h>
#include <QVector>

class Sommet
{
public:
    Sommet();
    Sommet(QVector3D point);
    Face* getFace();
    void setFace(Face* face);
    QVector3D getPoint() const;
    bool operator!=(Sommet const& a) const;

private:
    QVector3D point;
    Face* face;
};

#endif // SOMMET_H
