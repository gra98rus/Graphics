#include "systemcoordtransformer.h"

SystemCoordTransformer::SystemCoordTransformer()
{

}


QVector4D SystemCoordTransformer::screenToLocal(QVector2D coord, QImage &image){
    double x = coord.x();
    double y = 0;
    double z = image.height() - coord.y();
    double w = 1;
    return QVector4D(x, y, z, w);
}

QVector4D SystemCoordTransformer::transferOrigin(QVector4D coord, QVector4D t){
    QMatrix4x4 T = QMatrix4x4(1, 0, 0, -t.x(),
                              0, 1, 0, -t.y(),
                              0, 0, 1, -t.z(),
                              0, 0, 0, 1);
    return T*coord;
}

QVector4D SystemCoordTransformer::toScreen(QVector4D coord, QImage &image){
    double x = coord.x()*500 + image.width()/2;
    double y = image.height()/2 - coord.y()*500;
    double z = image.height()/2 - coord.z()*500;
    double w = 1;
    return QVector4D(x, y, z, w);
}

void SystemCoordTransformer::changeRotate(double alpha, double betta){

    QMatrix4x4 rotationXMatrix = QMatrix4x4(1, 0, 0, 0,
                                            0, cos(alpha), -sin(alpha), 0,
                                            0, sin(alpha), cos(alpha), 0,
                                            0, 0, 0, 1) ;

    QMatrix4x4 rotationZMatrix = QMatrix4x4(cos(betta), -sin(betta), 0, 0,
                                            sin(betta), cos(betta), 0, 0,
                                            0, 0, 1, 0,
                                            0, 0, 0, 1) ;

    fullRotate = rotationZMatrix*rotationXMatrix*fullRotate;
}

QVector4D SystemCoordTransformer::rotate(QVector4D r){
    return fullRotate*r;
}

QVector4D SystemCoordTransformer::scale(QVector4D r, double xs, double ys, double zs){
    QMatrix4x4 rotationMatrix = QMatrix4x4(xs, 0, 0, 0,
                                           0, ys, 0, 0,
                                           0, 0, zs, 0,
                                           0, 0, 0, 1);
    return rotationMatrix*r;
}

QVector4D SystemCoordTransformer::toCamera(QVector4D r, Camera camera){
    QVector<double> start = camera.getCoord();
    QVector<QVector4D> orts = camera.getOrt();
    orts[0].normalize();
    orts[1].normalize();
    orts[2].normalize();
    QMatrix4x4 cameraMatrix = QMatrix4x4(orts[0].x(), orts[0].y(), orts[0].z(), 0,
                                         orts[1].x(), orts[1].y(), orts[1].z(), 0,
                                         orts[2].x(), orts[2].y(), orts[2].z(), 0,
                                         0, 0, 0, 1)
                                            *
                              QMatrix4x4(
                                         1, 0, 0, -start[0],
                                         0, 1, 0, -start[1],
                                         0, 0, 1, -start[2],
                                         0, 0, 0, 1);
    return cameraMatrix*r;
}

QVector4D SystemCoordTransformer::clipping(QVector4D r, Camera camera){
    QVector<double> clipParam = camera.getClipp();

    double sh = clipParam[0];
    double sw = clipParam[1];
    double zf = clipParam[2];
    double zb = clipParam[3];
//    QMatrix4x4 clipp = QMatrix4x4(2*zf/sw, 0, 0, 0,
//                                  0, 2*zf/sh, 0, 0,
//                                  0, 0, zf/(zb-zf), -zb*zf/(zb-zf),
//                                  0, 0, 1, 0);

    QMatrix4x4 clipp = QMatrix4x4(1/tan(sh/2)/sw, 0, 0, 0,
                                  0, 1/tan(sh/2), 0, 0,
                                  0, 0, (zf+zb)/(zb-zf), 1,
                                  0, 0, -2*zf*zb/(zb-zf), 0);
  //  std::cout<<"finisf:  "<<(clipp*r).x()<<"   "<<(clipp*r).w()<<std::endl;
    r = clipp*r;
    r/=(r.w());

    return r;
}

QVector4D SystemCoordTransformer::perspective(QVector4D r, Camera camera){
    QMatrix4x4 perspect = QMatrix4x4(1, 0, 0, 0,
                                     0, 1, 0, 0,
                                     0, 0, 1, 0,
                                     0, -1/camera.getCoord()[1], 0, 1) ;
    r = perspect*r;
    r/= r.w();
//    std::cout<<"finisf:  "<<(r).x()<<"   "<<(r).w()<<std::endl;

    return r;

}
