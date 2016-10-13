#ifndef EDGE_H
#define EDGE_H
#include <face.h>
#include <QDebug>

class Edge
{
public:
    edge();
    int getF1();
    int getF2();
    void setF1(int f1);
    void setF2(int f2);

private:
    int f1;
    int f2;
    int nbTr;
};

#endif // EDGE_H
