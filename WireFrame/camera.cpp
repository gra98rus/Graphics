#include "camera.h"

Camera::Camera(){

}

Camera::Camera(QVector4D u, QVector4D v, QVector4D w, double xc, double yc, double zc){
    this->xc = xc;
    this->yc = yc;
    this->zc = zc;
    this->u = u;
    this->v = v;
    this->w = w;
}

QVector<double> Camera::getCoord(){
    QVector<double> ans = {xc, yc, zc};
    return ans;
}

QVector<QVector4D> Camera::getOrt(){
    QVector<QVector4D> ans = {u, v, w};
    return ans;
}

void Camera::setClipp(double sh, double sw, double zf, double zb){
    this->sh = sh;
    this->sw = sw;
    this->zf = zf;
    this->zb = zb;
}

QVector<double> Camera::getClipp(){
    QVector<double> ans = {sh, sw, zf, zb};
    return ans;
}

