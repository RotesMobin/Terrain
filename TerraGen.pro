#-------------------------------------------------
#
# Project created by QtCreator 2013-09-12T03:27:41
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TerraGen
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gldisplay.cpp \
    terrain.cpp \
    edge.cpp \
    face.cpp \
    mesh.cpp \
    sommet.cpp \
    perlin.cpp \
    vegetation.cpp

HEADERS  += mainwindow.h \
    gldisplay.h \
    terrain.h \
    edge.h \
    face.h \
    mesh.h \
    sommet.h \
    perlin.h \
    vegetation.h

FORMS    += mainwindow.ui

LIBS += -lOpengl32
install_it.path = $$OUT_PWD/Data
install_it.files = Data/*

INSTALLS += install_it

DISTFILES += \
    queen.off
