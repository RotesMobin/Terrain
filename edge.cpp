#include "edge.h"

Edge::edge()
{
   nbTr=0;
}

int Edge::getF1(){
    return f1;
}

int Edge::getF2(){
    return f2;
}


void Edge::setF1(int f1){
    this->f1=f1;
}

void Edge::setF2(int f2){
    this->f2=f2;
}
