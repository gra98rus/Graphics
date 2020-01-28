#ifndef SYSTEMCOORDTRANSFORMER_H
#define SYSTEMCOORDTRANSFORMER_H

#include <QVector>
#include <QVector2D>
#include <QVector4D>
#include <QMatrix4x4>
#include <math.h>
#include <QImage>
#include <iostream>
#include "camera.h"

class SystemCoordTransformer
{
public:
    SystemCoordTransformer();

    QVector4D screenToLocal(QVector2D coord, QImage &image);

    QVector4D transferOrigin(QVector4D coord, QVector4D T);

    QVector4D toScreen(QVector4D coord, QImage &image);

    QVector4D rotate(QVector4D r);

    void changeRotate(double alpha, double betta);

    QVector4D scale(QVector4D r, double xs, double ys, double zs);

    QVector4D toCamera(QVector4D r, Camera camera);

    QVector4D clipping(QVector4D r, Camera camera);

    QVector4D perspective(QVector4D r, Camera camera);

private:
    QMatrix4x4 T;
    QMatrix4x4 S;
    QMatrix4x4 R;

    QMatrix4x4 fullRotate = QMatrix4x4(1, 0, 0, 0,
                                       0, 1, 0, 0,
                                       0, 0, 1, 0,
                                       0, 0, 0, 1);

};

#endif // SYSTEMCOORDTRANSFORMER_H
