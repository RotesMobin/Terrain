#include "mainwindow.h"
#include <QApplication>
#include <QDir>
#include <QString>
#include <terrain.h>
#include <mesh.h>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Terrain terrain;
    terrain = Terrain(256, 256);

    terrain.generateTerrainFromNoise(1, 300,100,true);
    terrain.generateTerrainFromNoise(3, 50,100,true);
    terrain.generateTerrainFromNoise(5, 20,100,true);
    terrain.generateTerrainFromNoise(15, 10,100,true);
    terrain.generateTerrainFromNoise(50, 3,100,true);
    terrain.generateTerrainFromNoise(150, 1,100,true);

    terrain.positiveHeight();

    //terrain.initializeDirt();
    terrain.erode(5);
    terrain.initializeSlope();
    //terrain.waterErode(50);
    terrain.generateDirtMap();


    terrain.initNormal();
    terrain.initVeget(30,300);
    terrain.drawVeget();
    Mesh m = Mesh(terrain);
    m.saveAsObj(terrain);
    return 0;
}
