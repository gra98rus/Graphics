#include "item.h"

Item::Item(){

}

Item::Item(Spline &spline, double x, double y, double z, double scale){
    this->spline = &spline;
    xCoord = x;
    yCoord = y;
    zCoord = z;
    this->scale = scale;
}

void Item::draw(QImage &image, SystemCoordTransformer &transformer, Camera &camera){
    double t;
    QVector4D coord;
    QVector4D T;
    QVector4D r;
    QVector4D rOld(0,0,0,0);
    QVector2D point;
    QPainter painter(&image);
    QVector<QVector2D> splinePoints = spline->getControlPoints();
    QVector<QVector4D> temp;
    QVector<QVector4D> prevTemp;
    int count = 0;
    if(splinePoints.length() < 4)
        return;
    maxR = findMaxR(image, transformer);
    for(double fi = 0; fi <= 2 * M_PI; fi += M_PI / n){
        for(int i = 1; i < splinePoints.length()-2; i++){
            for(t = 0; t <= 1; t += 0.1){

                point = spline->getPoint(t, i);

                coord = transformer.screenToLocal(point, image);
                T = QVector4D(image.width()/2, 0, image.height()/2, 1);

                coord = transformer.transferOrigin(coord, T);

                r = QVector4D(coord.x()*cos(fi), coord.x()*sin(fi), coord.z(), 1);

                r = transformer.scale(r, 1/maxR, 1/maxR, 1/maxR);

                r = transformer.scale(r, scale, scale, scale);

                T = QVector4D(-xCoord, -yCoord, -zCoord, 1);
                r = transformer.transferOrigin(r, T);

                r = transformer.rotate(r);
                r = transformer.toCamera(r, camera);

                r = transformer.perspective(r, camera);

                r = transformer.toScreen(r, image);
                if ((i == 1) && (t < 0.1)) rOld = r;

                temp.append(r);

                if ((fi != 0) && (count%k == 0))
                    painter.drawLine(prevTemp[count].x(), prevTemp[count].z(), r.x(), r.z());


                painter.drawLine(r.x(), r.z(), rOld.x(), rOld.z());
                rOld = r;
                count++;

            }
        }
        prevTemp = temp;
        temp.clear();
        count = 0;
    }
}

double Item::findMaxR(QImage &image, SystemCoordTransformer &transformer){
    double t;
    QVector<QVector2D> splinePoints;
    QVector4D T;
    QVector4D r;
    double max = 0;
    for(t = 0; t <= 1; t += 0.1){
        splinePoints = spline->getPointByT(t);
        for(int i = 0; i < splinePoints.length(); i++){

            r = transformer.screenToLocal(splinePoints[i], image);
            T = QVector4D(image.width()/2, 0, image.height()/2, 1);

            r = transformer.transferOrigin(r, T);

            if(abs(r.x()) > max) max = abs(r.x());
            if(abs(r.y()) > max) max = abs(r.y());
            if(abs(r.z()) > max) max = abs(r.z());
        }
    }
    return max;
}

void Item::setScale(double scale){
    this->scale = scale;
}

void Item::setX(double x){
    xCoord = x;
}

void Item::setY(double y){
    yCoord = y;
}

void Item::setZ(double z){
    zCoord = z;
}

void Item::set_k(int k){
    this->k = k;
}

void Item::set_n(int n){
    this->n = n;
}
