#ifndef VEGETATION_H
#define VEGETATION_H


class vegetation
{
    bool hasSurvived=false;


    double dirtMin;
    double heightMax;
public:
    double age;
    double ageMax;
    double rayon;
    double slopeMax;
    int type;
    int x;
    int y;
    vegetation();
    vegetation(int type, int x, int y);
    bool IsAlived(double slope, double dirt, double height);
};

#endif // VEGETATION_H
