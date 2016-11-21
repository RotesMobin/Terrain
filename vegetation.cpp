#include "vegetation.h"

vegetation::vegetation()
{

}
vegetation::vegetation(int type, int x, int y){
    if(type==1){
        this->age=1;
        this->rayon=2;
        this->slopeMax=110;
        this->dirtMin=0.2;
        this->heightMax=180;
        this->ageMax=5;
    }else{
        this->age=1;
        this->rayon=1;
        this->slopeMax=90;
        this->dirtMin=0.1;
        this->heightMax=150;
        this->ageMax=3;
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


