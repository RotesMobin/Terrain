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
    Terrain(int width, int length);

    void loadFromHeightMap(QString name);
    void setHeightAt(int x, int y, double z);
    void setDirtAt(int x, int y, double dirtValue);
    void setTemperAt(int x, int y,double value);
    void setGradAt(int x, int y, QVector3D value);
    void generateTerrainFromNoise(double freq, double amp, double nbPoints, boolean ridge);
    double getHeightAt(int x, int y);
    double getDirtAt(int x, int y);
    double getTemperAt(int x, int y);
    QVector3D getGradAt(int x,int y);
    int getLength();
    int getWidth();

    void drawTriangle(QVector3D v1, QVector3D v2, QVector3D v3);
    void saveAsImage(QString name);
    void display();
    void erode();
    void initializeDirt();
    void initGradTemper();
    QVector<double> height;
    QVector<double> dirt;
    QVector<double> temper;
    QVector<QVector3D> grad;
private:

    int width;
    int length;

    int* V8(int x, int y);
};

#endif // TERRAIN_H
