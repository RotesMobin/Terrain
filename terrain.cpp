#include "terrain.h"

Terrain::Terrain()
{

}
Terrain::Terrain(int width, int lenght){
    this->width=width;
    this->lenght=lenght;
}


double Terrain::getHeightAt(int x, int y){
    if(height[(y*lenght)+x]){
        return height[(y*lenght)+x];
    }
    else{
        return -1;
    }
}
void Terrain::setHeightAt(int x,int y, double z){
    if(height[(y*lenght)+x]){
        height[(y*lenght)+x]=z;
    }
}

void Terrain::generateTerrainFromNoise(){
    double i,j;
    double freq=2;
    double amp=1;
    for(i=0;i<width;i++){
        for(j=0;j<lenght;j++){
            height.append(amp*(noise(i/(width/freq),j/(lenght/freq))));
            //qDebug()<<noise(i,j);
        }
    }
    freq=5;
    amp=0.1;
    for(i=0;i<width;i++){
        for(j=0;j<lenght;j++){
            height[(i*lenght)+j]+=amp*(noise(i/(width/freq),j/(lenght/freq)));
            //qDebug()<<noise(i,j);
        }
    }
    freq=10;
    amp=0.05;
    for(i=0;i<width;i++){
        for(j=0;j<lenght;j++){
            height[(i*lenght)+j]+=amp*(noise(i/(width/freq),j/(lenght/freq)));
            //qDebug()<<noise(i,j);
        }
    }
    saveAsImage("map.raw");
}

void Terrain::loadFromHeightMap(QString name){
    QImage map=QImage(name);
    int i,j;
    map.convertToFormat(QImage::Format_Indexed8);
    width=map.size().width();
    lenght=map.size().height();
    for(i=0;i<width;i++){
        for(j=0;j<lenght;j++){
            height.append(qGray(map.pixel(i,j)));
        }
    }
}

double Terrain::noise(double x, double y){
    float unit = 1.0/sqrt(2);
    QVector2D gradient2[8]= {{unit,unit},{-unit,unit},{unit,-unit},{-unit,-unit},
                       {1,0},      {-1,0},      {0,1},       {0,-1}};
    //On fait un masquage, ii et jj sont compris entre 0 et 255
    int x0=(int)floor(x);
    int y0=(int)floor(y);


    int x1=x0+1;
    int y1=y0+1;

    int ii = x0 % 125;
    int jj = y0 % 125;



    //Une manière un peu particulière de créer du désordre
    // Le modulo (%) 8 limite les valeurs de grad1 et grad4 entre 0 et 7
    int ind_grad1 = permtable[ii + permtable[jj]] % 8;
    int ind_grad2 = permtable[ii+1 + permtable[jj ]] % 8;
    int ind_grad3 = permtable[ii + 1 + permtable[jj+1]] % 8;
    int ind_grad4 = permtable[ii + permtable[jj + 1]] % 8;

    //On récupère simplement les valeurs des vecteurs
    QVector2D grad1 = gradient2[ind_grad1];
    QVector2D grad2 = gradient2[ind_grad2];
    QVector2D grad3 = gradient2[ind_grad3];
    QVector2D grad4 = gradient2[ind_grad4];

    QVector2D p1= QVector2D(x-(double)x0,y-(double)y0);
    QVector2D p2= QVector2D(x-(double)x1,y-(double)y0);
    QVector2D p3= QVector2D(x-(double)x1,y-(double)y1);
    QVector2D p4= QVector2D(x-(double)x0,y-(double)y1);

    double s = QVector2D::dotProduct(grad1,p1);
    double t = QVector2D::dotProduct(grad2,p2);
    double v = QVector2D::dotProduct(grad3,p3);
    double u = QVector2D::dotProduct(grad4,p4);

    double tmp = x-x0;

    double Cx = 3 * tmp * tmp - 2 * tmp * tmp * tmp;


    double Li1 = s + Cx*(t-s);

    double Li2 = u + Cx*(v-u);


    tmp = y - y0;

    double Cy = 3 * tmp * tmp - 2 * tmp * tmp * tmp;


    return Li1 + Cy*(Li2-Li1);
}

void Terrain::display(){
    int i=0;
    glColor3f(0.0,1.0,0.0);
    for(i=0;i<height.size();i++){
        glBegin(GL_POINTS);
        glVertex3f((((double)i/(double)lenght)/(double)lenght)-0.5
                   ,((double)(i%lenght)/(double)width)-0.5
                   ,height[i]);
        glEnd();
    }
}

void Terrain::saveAsImage(QString name){
    int i,gray;
    QImage map=QImage(width,lenght,QImage::Format_RGB32);
    for(i=0;i<height.size();i++){
        gray=qGray((height[i]+0.5)*255,(height[i]+0.5)*255,(height[i]+0.5)*255);
        map.setPixel(i/lenght,i%lenght,qRgb(gray,gray,gray));
    }

    qDebug()<<map.save("map.png");
}

int Terrain::getLenght(){
    return lenght;
}

int Terrain::getWidth(){
    return width;
}

