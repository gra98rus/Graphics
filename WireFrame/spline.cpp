#include "spline.h"

Spline::Spline()
{
    transformer = SystemCoordTransformer();
}

void Spline::draw(bool pointDraw, QImage &image){
    double x, y;
    double t;
    QMatrix4x4 Ms = QMatrix4x4(-1, 3, -3, 1,
                               3, -6, 3, 0,
                               -3, 0, 3, 0,
                               1, 4, 1, 0) * 1/6;
    QVector4D T;
    QVector4D temp;
    QPainter painter(&image);
    painter.setPen(QColor(255, 0, 0));
    if(pointDraw){
        for(int i = 0; i < controlPoints.length(); i++){
            painter.drawEllipse(QPoint(controlPoints[i].x(), controlPoints[i].y()), 25, 25);
            image.setPixel(controlPoints[i].x(), controlPoints[i].y(), qRgb(255,0,0));
            image.setPixel(controlPoints[i].x()-1, controlPoints[i].y(), qRgb(255,0,0));
            image.setPixel(controlPoints[i].x()+1, controlPoints[i].y(), qRgb(255,0,0));
            image.setPixel(controlPoints[i].x(), controlPoints[i].y()-1, qRgb(255,0,0));
            image.setPixel(controlPoints[i].x(), controlPoints[i].y()+1, qRgb(255,0,0));
        }
    }
    if(controlPoints.length() < 4)
        return;

    for(t = 0; t <= 1; t += 0.001){
        for(int i = 1; i < controlPoints.length() - 2; i++){
            T = QVector4D(pow(t, 3), pow(t, 2), t, 1);
            temp = (T*Ms);
            x = temp.x()*controlPoints[i-1].x() + temp.y()*controlPoints[i].x() + temp.z()*controlPoints[i+1].x() + temp.w()*controlPoints[i+2].x();
            y = temp.x()*controlPoints[i-1].y() + temp.y()*controlPoints[i].y() + temp.z()*controlPoints[i+1].y() + temp.w()*controlPoints[i+2].y();
            image.setPixel(x, y, qRgb(255,0,0));
        }
    }
}

void Spline::addControlPoint(double x, double y){
    controlPoints.append(QVector2D(x, y));
}

QVector<QVector2D> Spline::getPointByT(double t){
    double x, y;
    QVector<QVector2D> points;
    QVector4D T;
    QVector4D temp;
    QMatrix4x4 Ms = QMatrix4x4(-1, 3, -3, 1,
                               3, -6, 3, 0,
                               -3, 0, 3, 0,
                               1, 4, 1, 0) * 1/6;

    if(controlPoints.length() < 4)
        return(points);
    for(int i = 1; i < controlPoints.length() - 2; i++){
        T = QVector4D(pow(t, 3), pow(t, 2), t, 1);
        temp = (T*Ms);
        x = temp.x()*controlPoints[i-1].x() + temp.y()*controlPoints[i].x() + temp.z()*controlPoints[i+1].x() + temp.w()*controlPoints[i+2].x();
        y = temp.x()*controlPoints[i-1].y() + temp.y()*controlPoints[i].y() + temp.z()*controlPoints[i+1].y() + temp.w()*controlPoints[i+2].y();
        points.append(QVector2D(x, y));
    }
    return(points);
}

QVector2D Spline::getPoint(double t, int i){
    double x, y;
    QVector2D point;
    QVector4D T;
    QVector4D temp;
    QMatrix4x4 Ms = QMatrix4x4(-1, 3, -3, 1,
                               3, -6, 3, 0,
                               -3, 0, 3, 0,
                               1, 4, 1, 0) * 1/6;

    if(controlPoints.length() < 4)
        return(point);
    T = QVector4D(pow(t, 3), pow(t, 2), t, 1);
    temp = (T*Ms);
    x = temp.x()*controlPoints[i-1].x() + temp.y()*controlPoints[i].x() + temp.z()*controlPoints[i+1].x() + temp.w()*controlPoints[i+2].x();
    y = temp.x()*controlPoints[i-1].y() + temp.y()*controlPoints[i].y() + temp.z()*controlPoints[i+1].y() + temp.w()*controlPoints[i+2].y();
    point = QVector2D(x, y);
    return(point);
}

void Spline::deleteLastPoint(){
    if(controlPoints.length() != 0)
        controlPoints.pop_back();
}

QVector<QVector2D> Spline::getControlPoints(){
    return controlPoints;
}

void Spline::changeControlPoint(int i, QVector2D newPoint){
    if (i >= 0)
        controlPoints[i] = newPoint;
}
