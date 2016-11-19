#include "gldisplay.h"

#define FRUSTUM_SIZE 1.0f

GLDisplay::GLDisplay(QWidget *parent) :
    QGLWidget(parent),
    _angleX(0.0f),
    _angleY(0.0f)
{

}

void GLDisplay::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(1.0, 1.0, 0.0);

    terrain = Terrain(512, 512,512,512);

    terrain.generateTerrainFromNoise(2, 250,100,false);
    terrain.generateTerrainFromNoise(3, 50,100,true);
    terrain.generateTerrainFromNoise(5, 20,100,true);
    terrain.generateTerrainFromNoise(15, 10,100,true);
    terrain.generateTerrainFromNoise(50, 3,100,true);
    terrain.generateTerrainFromNoise(150, 1,100,true);

    terrain.initializeSlope();
    terrain.initializeDirt();
    terrain.erode();

    m = Mesh(terrain);
    m.saveAsObj(terrain);

    //terrain.loadFromHeightMap("Data/test2.png");
}

void GLDisplay::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    glRotatef(_angleX, 0.0f, 1.0f, 0.0f);
    glRotatef(_angleY, 1.0f, 0.0f, 0.0f);
    //resizeGL(terrain.getWidth(),terrain.getLenght());
    //terrain.display();
    //m.draw();
}

void GLDisplay::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);

    glViewport(0, 0, w, h);

    glOrtho(-FRUSTUM_SIZE, FRUSTUM_SIZE,
            -FRUSTUM_SIZE, FRUSTUM_SIZE,
            -FRUSTUM_SIZE, FRUSTUM_SIZE);

    glMatrixMode(GL_MODELVIEW);
}

void GLDisplay::mouseMoveEvent(QMouseEvent *event)
{
    if( event != NULL ) {
        QPoint position = event->pos();

        _angleX += (position.x() - _position.x());
        _angleY += (position.y() - _position.y());
        _position = position;

        updateGL();
    }
}

void GLDisplay::mousePressEvent(QMouseEvent *event)
{
    if( event != NULL )
        _position = event->pos();
}
