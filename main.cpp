#include "mainwindow.h"
#include <QApplication>
#include <iostream>

#include <QUrl>
#include <Qt3DRender/QMesh>
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/Qt3DWindow>
#include <QWidget>
#include <QColor>
#include <QRgb>
#include <QGuiApplication>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/qcamera.h>
#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcameralens.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtGui/QScreen>
#include <Qt3DInput/QInputAspect>
#include <Qt3DExtras/qtorusmesh.h>
#include <Qt3DRender/qmesh.h>
#include <Qt3DRender/qtechnique.h>
#include <Qt3DRender/qmaterial.h>
#include <Qt3DRender/qeffect.h>
#include <Qt3DRender/qtexture.h>
#include <Qt3DRender/qrenderpass.h>
#include <Qt3DRender/qsceneloader.h>
#include <Qt3DRender/qpointlight.h>
#include <Qt3DCore/qtransform.h>
#include <Qt3DCore/qaspectengine.h>
#include <Qt3DRender/qrenderaspect.h>
#include <Qt3DExtras/qforwardrenderer.h>
#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>
#include <QFileInfo>
#include <Qt3DRender/QFrontFace>
#include <Qt3DExtras/QOrbitCameraController>
#include <qgeometryrenderer.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

w.setWindowTitle("W window title");

// This is first attempt to work with Github


    w.show();

    return a.exec();
}
