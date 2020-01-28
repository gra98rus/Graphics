#ifndef CAMERA_H
#define CAMERA_H

#include <QVector4D>
#include <QVector>
#include <QMatrix4x4>

class Camera
{
public:
    Camera();

    Camera(QVector4D u, QVector4D v, QVector4D w, double xc, double yc, double zc);

   // QVector<double> getCoord();

    QVector4D getCoord();

    QVector<QVector4D> getOrt();

    void setClipp(double sh, double sb, double zf, double zb);

    QVector<double> getClipp();

private:
    double xc, yc, zc;
    QVector4D u, v, w;

    double sh, sw;
    double zf, zb;
};

#endif // CAMERA_H
