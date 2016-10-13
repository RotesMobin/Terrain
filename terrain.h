#ifndef TERRAIN_H
#define TERRAIN_H

#include <windows.h>
#include <QObject>
#include <QVector>
#include <GL/gl.h>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QVector3D>
#include <QVector2D>
#include <QRgb>
#include <QColor>
#include <math.h>
#include <perlin.h>

class Terrain
{
public:
    Terrain();
    Terrain(int width, int lenght);

    void loadFromHeightMap(QString name);
    void setHeightAt(int x, int y, double z);
    void setDirtAt(int x, int y, double dirtValue);
    void generateTerrainFromNoise(double Hfreq,double Hamp);
    double getHeightAt(int x, int y);
    double getDirtAt(int x, int y);
    int getLenght();
    int getWidth();

    void drawTriangle(QVector3D v1, QVector3D v2, QVector3D v3);
    void saveAsImage(QString name);
    void display();

private:
    QVector<double> height;
    QVector<double> dirt;
    int width;
    int lenght;
};

#endif // TERRAIN_H
