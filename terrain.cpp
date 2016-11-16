#include "terrain.h"

Terrain::Terrain()
{

}

Terrain::Terrain(int length, int width)
{
    this->width = width;
    this->length = length;

    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < length; j++)
        {
            height.append(0);
            dirt.append(0);
        }
    }
}

double Terrain::getHeightAt(int x, int y)
{
    if(x >= 0 && y >= 0 && x < width && y < length)
    {
        return height[(y * width) + x];
    }
    else
    {
        return -1;
    }
}

double Terrain::getDirtAt(int x, int y)
{
    if(x >= 0 && y >= 0 && x < width && y < length)
    {
        return dirt[(y * width) + x];
    }
    else
    {
        return -1;
    }
}

double Terrain::getTemperAt(int x, int y){
    if(x >= 0 && y >= 0 && x < width && y < length)
    {
        return temper[(y * width) + x];
    }
    else
    {
        return -1;
    }
}

QVector3D Terrain::getGradAt(int x, int y){
    if(x >= 0 && y >= 0 && x < width && y < length)
    {
        return grad[(y * width) + x];
    }
    else
    {
        return std::nullptr_t;
    }
}

void Terrain::setGradAt(int x, int y,QVector3D value){
    if(x >= 0 && y >= 0 && x < width && y < length)
    {
        grad[(y * width) + x] = value;
    }
}

void Terrain::setTemperAt(int x, int y,double value){
    if(x >= 0 && y >= 0 && x < width && y < length)
    {
        temper[(y * width) + x] = value;
    }
}

void Terrain::setHeightAt(int x, int y, double z)
{
    if(x >= 0 && y >= 0 && x < width && y < length)
    {
        height[(y * width) + x] = z;
    }
}

void Terrain::setDirtAt(int x, int y, double dirtValue)
{
    if(x >= 0 && y >= 0 && x < width && y < length)
    {
        dirt[(y * width) + x] = dirtValue;
    }
}

void Terrain::generateTerrainFromNoise(double freq, double amp, double nbPoints, boolean ridge)
{
    double i, j;
    double h;
    Perlin perlin = Perlin();

    for(i = 0; i < width; i++)
    {
        for(j = 0; j < length; j++)
        {
            h=amp * (perlin.noise(i*freq /width , j*freq /length ));
            if(ridge){
                if(h>amp/4){
                    height[(j*width)+i] -= (h-amp/4)*2;
                }
                if(h<(-amp/4)){
                    height[(j*width)+i] -= (h+amp/4)*2;
                }
            }
            height[(j*width)+i] += h;

        }
    }
    //saveAsImage("map.raw");
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

void Terrain::initGradTemper(){
    double z;
    for(int i=0;i<width;i++){
        for(int j=0;j<length;j++){
            z=getHeightAt(i,j);

        }
    }
}

void Terrain::initializeDirt()
{
    double max = *std::max_element(height.constBegin(), height.constEnd());
    double baseDirtValue = max / 10;

    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < length; j++)
        {
            setDirtAt(i, j, baseDirtValue);
        }
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

    if (x + 1 < length)
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

    if (y + 1 < width)
    {
        ret[2] = getHeightAt(x, y + 1);
    }

    if (x > 0 && y > 0)
    {
        ret[5] = getHeightAt(x - 1, y - 1);
    }

    if (x + 1 < length && y > 0)
    {
        ret[7] = getHeightAt(x + 1, y - 1);
    }

    if (y + 1 < width && x > 0)
    {
        ret[3] = getHeightAt(x - 1, y + 1);
    }

    if (y + 1 < width && x + 1 < length)
    {
        ret[1] = getHeightAt(x + 1, y + 1);
    }

    return &ret[0];
}
