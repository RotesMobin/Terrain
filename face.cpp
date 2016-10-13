#include "face.h"
Face::Face(){

}

Face::Face(int id,int s1,int s2,int s3){
    this->id=id;
    this->s1=s1;
    this->s2=s2;
    this->s3=s3;
    this->t1=-1;
    this->t2=-1;
    this->t3=-1;
}
int Face::getId() const{
    return id;
}
void Face::setId(int id){
    this->id=id;
}

int Face::getS1() const{
    return s1;
}
int Face::getS2() const{
    return s2;
}
int Face::getS3() const{
    return s3;
}

void Face::setS1(int s1){
    this->s1=s1;
}
void Face::setS2(int s2){
    this->s2=s2;
}
void Face::setS3(int s3){
    this->s3=s3;
}

int Face::getT1() const{
    return t1;
}

int Face::getT2() const{
    return t2;
}

int Face::getT3() const{
    return t3;
}

void Face::setT1(int t1){
    this->t1=t1;
}

void Face::setT2(int t2){
    this->t2=t2;
}

void Face::setT3(int t3){
    this->t3=t3;
}
void Face::addTr(int tr){
    if(t1==-1){
        t1=tr;
    }
    else if(t2==-1){
        t2=tr;
    }
    else if(t3==-1){
        t3=tr;
    }
    else{
       printf("Déja 3 tr !%d\n",id);
    }
}
bool Face::operator!=(Face const& a){
    return this->getS1()!=a.getS1() || this->getS2()!= a.getS2() || this->getS3()!=a.getS3();
}























