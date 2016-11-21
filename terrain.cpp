#include "terrain.h"
#include <QtMath>

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
            norm.append(QVector3D());
            avgSlope.append(0);
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

double Terrain::getTemperAt(int x, int y)
{
    if(x >= 0 && y >= 0 && x < width && y < length)
    {
        return temper[(y * width) + x];
    }
    else
    {
        return -1;
    }
}

QVector3D Terrain::getNormAt(int x, int y)
{
    if(x >= 0 && y >= 0 && x < width && y < length)
    {
        return norm[(y * width) + x];
    }
    else
    {
        return QVector3D();
    }
}

double Terrain::getAvgSlope(int x, int y)
{
    if(x >= 0 && y >= 0 && x < width && y < length)
    {
        return avgSlope[(y * width) + x];
    }
    else
    {
        return -1;
    }
}

vegetation Terrain::getVeget(int x,int y){
    if(x >= 0 && y >= 0 && x < width && y < length)
    {
        return veget[(y * width) + x];
    }
    else
    {
        return vegetation();
    }
}

void Terrain::setVeget(int x, int y, vegetation value){
    if(x >= 0 && y >= 0 && x < width && y < length)
    {
        veget[(y * width) + x] = value;
    }
}

void Terrain::setNormAt(int x, int y,QVector3D value)
{
    if(x >= 0 && y >= 0 && x < width && y < length)
    {
        norm[(y * width) + x] = value;
    }
}

void Terrain::setTemperAt(int x, int y,double value)
{
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

void Terrain::setAvgSlope(int x, int y, double value)
{
    if(x >= 0 && y >= 0 && x < width && y < length)
    {
        avgSlope[(y * width) + x] = value;
    }
}

void Terrain::generateTerrainFromNoise(double freq, double amp,int start, boolean ridge)
{
    double i, j;
    double h;
    int periode = 500;
    float ridge_val;
    Perlin perlin = Perlin();

    for(i = 0; i < width; i++)
    {
        for(j = 0; j < length; j++)
        {

            ridge_val=amp *perlin.noise((i+start+1500)*freq /periode , (j+start+1500)*freq /periode);
            h=amp * (perlin.noise((i+start)*freq /periode , (j+start)*freq /periode));

            if(ridge){
                if(h<ridge_val){
                    //height[(j*width)+i] -= (h-ridge_val)*2;
                    height[(j*width)+i] += h;
                }
                else{
                    height[(j*width)+i] += ridge_val;
                }
            }
            else{
                height[(j*width)+i] += h;
            }
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
    int ite, rand;
    QVector3D base, target;
    double dot, lenSq1, lenSq2, angle;
    double* v8;

    ite = rand = dot = lenSq1 = lenSq2 = angle = 0;

    while(ite < 10000)
    {
        for(int i = 0; i < width; i++)
        {
            for(int j = 0; j < length; j++)
            {
                if(qrand() % 1000 + 1 == 1)
                {
                    // Erosion Th
                    v8 = V8(i, j);

                    for(int s = 0; s < 8; s++)
                    {
                        if(v8[s] > 0)
                        {
                            switch(s)
                            {
                                case 0:
                                    base = QVector3D(1, 0, 0);
                                    target = QVector3D(1, 0, getHeightAt(i + 1, j) + getDirtAt(i + 1, j) - getHeightAt(i, j) - getDirtAt(i, j));
                                break;

                                case 1:
                                    base = QVector3D(1, 1, 0);
                                    target = QVector3D(1, 1, getHeightAt(i + 1, j + 1) + getDirtAt(i + 1, j + 1) - getHeightAt(i, j) - getDirtAt(i, j));
                                break;

                                case 2:
                                    base = QVector3D(0, 1, 0);
                                    target = QVector3D(0, 1, getHeightAt(i, j + 1) + getDirtAt(i, j + 1) - getHeightAt(i, j) - getDirtAt(i, j));
                                break;

                                case 3:
                                    base = QVector3D(-1, 1, 0);
                                    target = QVector3D(-1, 1, getHeightAt(i - 1, j + 1) + getDirtAt(i - 1, j + 1) - getHeightAt(i, j) - getDirtAt(i, j));
                                break;

                                case 4:
                                    base = QVector3D(-1, 0, 0);
                                    target = QVector3D(-1, 0, getHeightAt(i - 1, j) + getDirtAt(i - 1, j) - getHeightAt(i, j) - getDirtAt(i, j));
                                break;

                                case 5:
                                    base = QVector3D(-1, -1, 0);
                                    target = QVector3D(-1, -1, getHeightAt(i - 1, j - 1) + getDirtAt(i - 1, j - 1) - getHeightAt(i, j) - getDirtAt(i, j));
                                break;

                                case 6:
                                    base = QVector3D(0, -1, 0);
                                    target = QVector3D(0, -1, getHeightAt(i, j - 1) + getDirtAt(i, j - 1) - getHeightAt(i, j) - getDirtAt(i, j));
                                break;

                                case 7:
                                    base = QVector3D(1, -1, 0);
                                    target = QVector3D(1, -1, getHeightAt(i + 1, j - 1) + getDirtAt(i + 1, j - 1) - getHeightAt(i, j) - getDirtAt(i, j));
                                break;

                            }

                            // Compute angle between base and target vectors in degrees
                            base.normalize();
                            target.normalize();
                            dot = base.dotProduct(base, target);
                            lenSq1 = base.x() * base.x() + base.y() * base.y() + base.z() * base.z();
                            lenSq2 = target.x() * target.x() + target.y() * target.y() + target.z() * target.z();
                            angle = qRadiansToDegrees(acos(dot / sqrt(lenSq1 * lenSq2)));

                        }
                    }
                }
            }
        }

        ite++;
    }
}
void Terrain::initVeget(int nbveget, int nbCycles){
    veget= QVector<vegetation>();
    srand (time(NULL));
    //randp.min()
    int x,y,type;
    for (int t=0;t<nbveget;t++){
        x = 0 + static_cast <int> (rand()) /( static_cast <int> (RAND_MAX/(width-0)));
        y = 0 + static_cast <int> (rand()) /( static_cast <int> (RAND_MAX/(length-0)));
        type= 1 + static_cast <int> (rand()) /( static_cast <int> (RAND_MAX/(2-1)));
        vegetation toAdd=vegetation(type,x,y);;
        if(!checkVeget(toAdd.x,toAdd.y)){
            if(toAdd.IsAlived(getAvgSlope(x,y),getDirtAt(x,y),getHeightAt(x,y))){
                veget.append(toAdd);
            }
        }
    }


}

void Terrain::drawVeget(){
    QPixmap* map=new QPixmap(width,length);
    QPainter painter;
    painter.begin(map);
    painter.setPen(QColor("red"));
    for(int i=0;i<veget.count();i++){
        painter.drawEllipse(QPoint(veget[i].x,veget[i].y),veget[i].rayon,veget[i].rayon);
    }
    map->save("Veget.png");
    painter.end();
    delete map;
}

bool Terrain::checkVeget(int x, int y){
    for(int i=0;i<veget.count();i++){
        if(veget[i].x==x&&veget[i].y==y){
            return true;
        }
    }
    return false;
}

void Terrain::initNormal(){
    double z,zx1,zx0,zy1,zy0,dx,dy;
    for(int i=0;i<width;i++){
        for(int j=0;j<length;j++){
            z=getHeightAt(i,j);
            if(i+1<width&&i-1>0&&j+1<length&&j-1>0){
                zx1=getHeightAt(i+1,j);
                zx0=getHeightAt(i-1,j);
                zy1=getHeightAt(i,j+1);
                zy0= getHeightAt(i,j-1);
                dx=(zx1-zx0)/2;
                dy=(zy1-zy0)/2;
                setNormAt(i,j,QVector3D(-dx,-dy,1));
           }

        }
    }
}

void Terrain::positiveHeight(){
    double min = *std::min_element(height.constBegin(), height.constEnd());

    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < length; j++)
        {
            setHeightAt(i, j, getHeightAt(i, j) + abs(min));
        }
    }

}

void Terrain::initializeSlope()
{
    int count = 0;
    double* v8;
    double slope, temp;
    slope = temp = 0;

    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < length; j++)
        {
            v8 = V8(i, j);
            count = 0;
            temp = 0;

            for(int s = 0; s < 8; s++)
            {
                if(v8[s] > 0)
                {
                    temp += abs(v8[s]);
                    count++;
                }
            }

            setAvgSlope(i, j, temp / count);
        }
    }

    int gray, val;
    QImage map = QImage(width, length, QImage::Format_RGB32);
    double max = *std::max_element(height.constBegin(), height.constEnd());

    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < length; j++)
        {
            val = (int)getAvgSlope(i, j) / max * 255;
            gray = qGray(val, val, val);
            map.setPixel(i, j, qRgb(val, 50, 255 - val));
        }
    }

    qDebug() << map.save("SlopeMap.png");
}

void Terrain::initializeDirt()
{
    double max = *std::max_element(height.constBegin(), height.constEnd());
    double baseDirtValue = max / 10;

    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < length; j++)
        {
            if(j < length / 2)
                setDirtAt(i, j, 0.3);
            else
                setDirtAt(i, j, 0.2);
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

double* Terrain::V8(int x, int y)
{
    double* ret = new double[8];

    for(int i = 0; i < 8; i++)
    {
        ret[i] = 0;
    }

    if (x + 1 < length)
    {
        ret[0] = getHeightAt(x + 1, y) + getDirtAt(x + 1, y);
    }

    if (x > 0)
    {
        ret[4] = getHeightAt(x - 1, y) + getDirtAt(x - 1, y);
    }

    if (y > 0)
    {
        ret[6] = getHeightAt(x, y - 1) + getDirtAt(x, y - 1);
    }

    if (y + 1 < width)
    {
        ret[2] = getHeightAt(x, y + 1) + getDirtAt(x, y + 1);
    }

    if (x > 0 && y > 0)
    {
        ret[5] = getHeightAt(x - 1, y - 1) + getDirtAt(x - 1, y - 1);
    }

    if (x + 1 < length && y > 0)
    {
        ret[7] = getHeightAt(x + 1, y - 1) + getDirtAt(x + 1, y - 1);
    }

    if (y + 1 < width && x > 0)
    {
        ret[3] = getHeightAt(x - 1, y + 1) + getDirtAt(x - 1, y + 1);
    }

    if (y + 1 < width && x + 1 < length)
    {
        ret[1] = getHeightAt(x + 1, y + 1) + getDirtAt(x + 1, y + 1);
    }

    return ret;
}
