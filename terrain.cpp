#include "terrain.h"

Terrain::Terrain()
{

}

Terrain::Terrain(int width, int length)
{
    this->width = width;
    this->length = length;
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < length; j++)
        {
            height.append(0);
        }
    }
}

double Terrain::getHeightAt(int x, int y)
{
    if(height[(y * length) + x])
    {
        return height[(y * length) + x];
    }
    else
    {
        return -1;
    }
}

double Terrain::getDirtAt(int x, int y)
{
    if(dirt[(y * length) + x])
    {
        return dirt[(y * length) + x];
    }
    else
    {
        return -1;
    }
}

void Terrain::setHeightAt(int x, int y, double z)
{
    if(height[(y * length) + x])
    {
        height[(y * length) + x] = z;
    }
}

void Terrain::setDirtAt(int x, int y, double dirtValue)
{
    if(dirt[(y * length) + x])
    {
        dirt[(y * length) + x] = dirtValue;
    }
}

void Terrain::generateTerrainFromNoise(double freq, double amp)
{
    double i, j;
    Perlin perlin = Perlin();

    for(i = 0; i < width; i++)
    {
        for(j = 0; j < length; j++)
        {
            height[(i*length)+j] += amp * (perlin.noise(i / (width / freq), j / (length / freq)));
            //qDebug() << height[(i*lenght)+j];
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
    length = map.size().height();

    for(i = 0; i < width; i++)
    {
        for(j = 0; j < length; j++)
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

        glVertex3f((((double)i/(double)length)/(double)length)-0.5
                   ,((double)(i%length)/(double)width)-0.5
                   ,height[i]);
        glEnd();
    }
}

void Terrain::saveAsImage(QString name)
{
    int i, gray;
    QImage map = QImage(width, length, QImage::Format_RGB32);

    for(i = 0; i < height.size(); i++)
    {
        gray = qGray((height[i] + 0.5) * 255, (height[i] + 0.5) * 255, (height[i] + 0.5) * 255);
        map.setPixel(i / length, i % length, qRgb(gray, gray, gray));
    }

    qDebug()<<map.save("map.png");
}

void Terrain::erode()
{
    int ite = 0;

    while(ite < 10000)
    {
        for(int i = 0; i < width; i++)
        {
            for(int j = 0; j < length; j++)
            {
                // Erosion Th

                // Mouvement Dirt
            }
        }

        ite++;
    }
}

int Terrain::getLength()
{
    return length;
}
int Terrain::getWidth()
{
    return width;
}

int* Terrain::V8(int x, int y)
{
    int ret[8];

    if (x + 1 < width)
    {
        ret[0] = getHeightAt(x + 1, y);
    }

    if (x > 0)
    {
        ret[4] = getHeightAt(x - 1, y);
    }

    if (y > 0)
    {
        ret[6] = getHeightAt(x, y - 1);
    }

    if (y + 1 < length)
    {
        ret[2] = getHeightAt(x, y + 1);
    }

    if (x > 0 && y > 0)
    {
        ret[5] = getHeightAt(x - 1, y - 1);
    }

    if (x + 1 < width && y > 0)
    {
        ret[7] = getHeightAt(x + 1, y - 1);
    }

    if (y + 1 < length && x > 0)
    {
        ret[3] = getHeightAt(x - 1, y + 1);
    }

    if (y + 1 < length && x + 1 < width)
    {
        ret[1] = getHeightAt(x + 1, y + 1);
    }

    return &ret[0];
}
