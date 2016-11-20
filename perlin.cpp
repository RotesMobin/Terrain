#include "perlin.h"
#include <math.h>
#include <QVector2D>

Perlin::Perlin()
{

}
double Perlin::cubic_poly(const double t)
{
    return 3*std::pow(t,2)-2*pow(t,3);
}
double Perlin::quintic_poly(const double t)
{
    const double t3 = t * t * t;
    return t3 * (t * (t * 6. - 15.) + 10.);
}

int Perlin::RandomGrad(int i, int j){
    return permtable[i + permtable[j]] % 8;
}

double Perlin::noise(double x, double y, double* n)
{
    QVector2D gradient2[8] = {{1,1},{-1,1},{1,-1},{-1,-1},
                       {1,0}, {-1,0}, {0,1}, {0,-1}};

    // On fait un masquage, ii et jj sont compris entre 0 et 255
    int x0 = (int)floor(x);
    int y0 = (int)floor(y);


    int x1 = x0 + 1;
    int y1 = y0 + 1;

    int ii = x0 % 256;
    int jj = y0 % 256;



    // Une manière un peu particulière de créer du désordre
    // Le modulo (%) 8 limite les valeurs de grad1 et grad4 entre 0 et 7
    int ind_grad1 = RandomGrad(ii,jj);
    int ind_grad2 = RandomGrad(ii+1,jj);
    int ind_grad3 = RandomGrad(ii+1,jj+1);
    int ind_grad4 = RandomGrad(ii,jj+1);

    // On récupère simplement les valeurs des vecteurs
    QVector2D grad1 = gradient2[ind_grad1];
    QVector2D grad2 = gradient2[ind_grad2];
    QVector2D grad3 = gradient2[ind_grad3];
    QVector2D grad4 = gradient2[ind_grad4];

    QVector2D p1 = QVector2D(x - (double)x0, y - (double)y0);
    QVector2D p2 = QVector2D(x - (double)x1, y - (double)y0);
    QVector2D p3 = QVector2D(x - (double)x1, y - (double)y1);
    QVector2D p4 = QVector2D(x - (double)x0, y - (double)y1);

    double s = QVector2D::dotProduct(grad1, p1);
    double t = QVector2D::dotProduct(grad2, p2);
    double v = QVector2D::dotProduct(grad3, p3);
    double u = QVector2D::dotProduct(grad4, p4);

    double tmp = x - x0;
    double Cx = quintic_poly(tmp);


    double Li1 = s + Cx*(t-s);

    double Li2 = u + Cx*(v-u);


    tmp = y - y0;

    double Cy = quintic_poly(tmp);

    return Li1 + Cy*(Li2 - Li1);
}
