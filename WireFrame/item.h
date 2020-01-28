#ifndef ITEM_H
#define ITEM_H

#include <QImage>
#include <QVector>
#include <QVector2D>
#include <QVector4D>
#include <QMatrix4x4>
#include "spline.h"
#include <math.h>
#include <iostream>
#include "systemcoordtransformer.h"
#include "camera.h"


class Item
{
public:
    Item();

    Item(Spline &spline, double x, double y, double z, double scale);

    void draw(QImage &image, SystemCoordTransformer &transformer, Camera &camera);

    void setScale(double scale);

    void setX(double x);

    void setY(double y);

    void setZ(double z);

    void set_n(int n);

    void set_k(int k);
private:

    double findMaxR(QImage &image, SystemCoordTransformer &transformer);

    Spline * spline;

    double xCoord;
    double yCoord;
    double zCoord;

    int n = 10;
    int k = 10;

    double maxR;

    double scale;

    Camera camera;
};

#endif // ITEM_H
