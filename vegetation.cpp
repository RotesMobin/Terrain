#include "vegetation.h"

vegetation::vegetation()
{

}
vegetation::vegetation(int type, int x, int y){
    if(type==1){
        this->rayon=1;
        this->slopeMax=60;
        this->dirtMin=0.2;
    }else{
        this->rayon=1.5;
        this->slopeMax=40;
        this->dirtMin=0.3;
    }
    this->x=x;
    this->y=y;
}

bool vegetation::IsAlived(double slope, double dirt, double height){
    if(this->dirtMin<dirt&&slope<slopeMax&&height<heightMax){
        return true;
    }
    return false;
}


