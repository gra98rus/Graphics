#ifndef MODEL_H
#define MODEL_H

#include <QImage>
#include "spline.h"
#include "item.h"
#include "systemcoordtransformer.h"
#include <QVector>
#include "camera.h"
#include "lightsource.h"

class Model
{
public:
    Model();

    void draw(QImage &image);

    void drawSpline(bool pointDraw, QImage &image);

    void addPointSpline(double x, double y);

    void addSplineForItem(Spline & spline, double x, double y, double z, double scale);

    void deleteLastItem();

    void drawCube(QImage &image);

    void addRotate(double alpha, double betta);

    void setScaleItem(double scale, int i);

    void setXItem(double x, int i);

    void setYItem(double y, int i);

    void setZItem(double z, int i);

    void set_nItem(int n, int i);

    void set_kItem(int k, int i);

    Spline getSpline(int i);

    void setSpline(Spline spline, int i);

private:
    SystemCoordTransformer transformer;

    double xMaxModel = 100;
    double yMaxModel = 100;
    double zMaxModel = 100;

    QVector<Spline*> splines;
    QVector<Item*> items;
    Camera camera;
    LightSource lightSourse;// = LightSource(QVector4D(2, 2, 2, 1));


    QVector<QVector2D> controlPoints = {QVector2D(100, 100), QVector2D(150, 120), QVector2D(400, 500), QVector2D(800, 700), QVector2D(900, 920), QVector2D(700, 300)};
    Spline splineTest = Spline(controlPoints);
    Item * itemTest = new Item(splineTest, 0, 0, 0, 1);
};

#endif // MODEL_H
