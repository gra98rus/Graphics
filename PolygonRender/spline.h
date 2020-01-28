#ifndef SPLINE_H
#define SPLINE_H

#include <QVector>
#include <QVector2D>
#include <QVector4D>
#include <QImage>
#include <QMatrix4x4>
#include <math.h>
#include <iostream>
#include <QPainter>
#include <QGenericMatrix>
#include "systemcoordtransformer.h"

class Spline
{
public:
    Spline();

    Spline(QVector<QVector2D> controlPoints);

    void draw(bool pointDraw, QImage &image);

    void addControlPoint(double x, double y);

    QVector<QVector2D> getPointByT(double t);

    QVector2D getPoint(double t, int i);

    QVector<QVector2D> getControlPoints();

    void deleteLastPoint();

    void changeControlPoint(int i, QVector2D newPoint);

private:   
    QVector<QVector2D> controlPoints;

    SystemCoordTransformer transformer;
};

#endif // SPLINE_H
