#include "mainwindow.h"
#include <QApplication>
#include <QDir>
#include <QString>
#include <terrain.h>
#include <mesh.h>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Terrain terrain = Terrain(512, 512);

    terrain.generateTerrainFromNoise(1, 300,100,true);
    terrain.generateTerrainFromNoise(3, 50,100,true);
    terrain.generateTerrainFromNoise(5, 20,100,true);
    terrain.generateTerrainFromNoise(15, 10,100,true);
    terrain.generateTerrainFromNoise(50, 3,100,true);
    terrain.generateTerrainFromNoise(150, 1,100,true);

    terrain.positiveHeight();

    terrain.initializeSlope();
    terrain.initializeDirt();
    //terrain.erode();
    terrain.initNormal();
    terrain.initVeget(300,2);
    terrain.drawVeget();
    Mesh m = Mesh(terrain);
    m.saveAsObj(terrain);
    return 0;
}
