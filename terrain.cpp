#include "terrain.h"

Terrain::Terrain()
{

}
Terrain::Terrain(int width, int lenght)
{
    this->width = width;
    this->lenght = lenght;
}

double Terrain::getHeightAt(int x, int y)
{
    if(height[(y * lenght) + x])
    {
        return height[(y * lenght) + x];
    }
    else
    {
        return -1;
    }
}

double Terrain::getDirtAt(int x, int y)
{
    if(dirt[(y * lenght) + x])
    {
        return dirt[(y * lenght) + x];
    }
    else
    {
        return -1;
    }
}

void Terrain::setHeightAt(int x, int y, double z)
{
    if(height[(y * lenght) + x])
    {
        height[(y * lenght) + x] = z;
    }
}

void Terrain::setDirtAt(int x, int y, double dirtValue)
{
    if(dirt[(y * lenght) + x])
    {
        dirt[(y * lenght) + x] = dirtValue;
    }
}

void Terrain::generateTerrainFromNoise()
{
    double i, j;
    double freq = 2;
    double amp = 1;
    Perlin perlin = Perlin();

    for(i = 0; i < width; i++)
    {
        for(j = 0; j < lenght; j++)
        {
            height.append(amp * (perlin.noise(i / (width / freq), j / (lenght / freq))));
            //qDebug()<<noise(i,j);
        }
    }

    freq=5;
    amp=0.1;
    for(i=0;i<width;i++){
        for(j=0;j<lenght;j++){
            height[(i*lenght)+j]+=amp*(perlin.noise(i/(width/freq),j/(lenght/freq)));
            //qDebug()<<noise(i,j);
        }
    }
    freq=10;
    amp=0.05;
    for(i=0;i<width;i++){
        for(j=0;j<lenght;j++){
            height[(i*lenght)+j]+=amp*(perlin.noise(i/(width/freq),j/(lenght/freq)));
            //qDebug()<<noise(i,j);
        }
    }
    saveAsImage("map.raw");
}

void Terrain::loadFromHeightMap(QString name)
{
    QImage map = QImage(name);
    int i, j;

    map.convertToFormat(QImage::Format_Indexed8);

    width = map.size().width();
    lenght = map.size().height();

    for(i = 0; i < width; i++)
    {
        for(j = 0; j < lenght; j++)
        {
            height.append(qGray(map.pixel(i,j)));
        }
    }
}

void Terrain::display()
{
    int i = 0;
    glColor3f(0.0, 1.0, 0.0);

    for(i = 0; i < height.size(); i++)
    {
        glBegin(GL_POINTS);

        glVertex3f((((double)i/(double)lenght)/(double)lenght)-0.5
                   ,((double)(i%lenght)/(double)width)-0.5
                   ,height[i]);
        glEnd();
    }
}

void Terrain::saveAsImage(QString name)
{
    int i, gray;
    QImage map = QImage(width,lenght,QImage::Format_RGB32);

    for(i = 0; i < height.size(); i++)
    {
        gray = qGray((height[i] + 0.5) * 255, (height[i] + 0.5) * 255, (height[i] + 0.5) * 255);
        map.setPixel(i / lenght, i % lenght, qRgb(gray, gray, gray));
    }

    qDebug()<<map.save("map.png");
}

int Terrain::getLenght()
{
    return lenght;
}

int Terrain::getWidth()
{
    return width;
}
