#ifndef VEGETATION_H
#define VEGETATION_H


class vegetation
{
    bool hasSurvived=false;


    double slopeMax;
    double dirtMin;
    double heightMax;
public:
    double rayon;

    int x;
    int y;
    vegetation();
    vegetation(int type, int x, int y);
    bool IsAlived(double slope, double dirt, double height);
};

#endif // VEGETATION_H
