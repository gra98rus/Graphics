#include "model.h"

Model::Model(){
    transformer = SystemCoordTransformer();
    camera = Camera(QVector4D(1, 0, 0, 1), QVector4D(0, 1, 0, 1), QVector4D(0, 0, 1, 1), 0, -10, -0);
    camera.setClipp(1, 1, 1.5, 10.5);
    lightSourse = LightSource(QVector4D(2, -2, 2, 1));
}

void Model::draw(QImage &image){
    for(int i = 0; i < items.length(); i++){
        items[i]->draw(image, transformer, camera, lightSourse);
    }
    drawCube(image);
}

void Model::drawSpline(bool pointDraw, QImage &image){
    for(int i = 0; i < splines.length(); i++)
        splines[i]->draw(pointDraw, image);
    for(int i = 0; i < image.height(); i++){
        image.setPixel(image.width()/2, i, qRgb(0, 255, 0));
    }
    for(int i = 0; i < image.width(); i++){
        image.setPixel(i, image.height()/2, qRgb(0, 255, 0));
    }
}

void Model::addSplineForItem(Spline &spline, double x, double y, double z, double scale){
    splines.append(new Spline(spline));
    items.append(new Item(*splines.last(), x, y, z, scale));
}

void Model::deleteLastItem(){
    if(items.length() > 0){
        items.pop_back();
        splines.pop_back();
    }
}

void Model::drawCube(QImage &image){
    QPainter painter(&image);
    QVector4D T;
    QVector<QVector4D> cube;
    cube.append(QVector4D(1, 1, 1, 1));
    cube.append(QVector4D(1, 1, -1, 1));
    cube.append(QVector4D(1, -1, 1, 1));
    cube.append(QVector4D(1, -1, -1, 1));
    cube.append(QVector4D(-1, 1, 1, 1));
    cube.append(QVector4D(-1, 1, -1, 1));
    cube.append(QVector4D(-1, -1, 1, 1));
    cube.append(QVector4D(-1, -1, -1, 1));

    QVector<QVector4D> axis;
    axis.append(QVector4D(0, 0, 0, 1));
    axis.append(QVector4D(0.5, 0, 0, 1));
    axis.append(QVector4D(0, 0.5, 0, 1));
    axis.append(QVector4D(0, 0, 0.5, 1));

    for (int i = 0; i < cube.length(); i++){

        cube[i] = transformer.transferOrigin(cube[i], T);

        cube[i] = transformer.rotate(cube[i]);
        cube[i] = transformer.toCamera(cube[i], camera);

        cube[i] = transformer.perspective(cube[i], camera);

        cube[i] = transformer.toScreen(cube[i], image);
    }

    for (int i = 0; i < axis.length(); i++){

        axis[i] = transformer.transferOrigin(axis[i], T);

        axis[i] = transformer.rotate(axis[i]);
        axis[i] = transformer.toCamera(axis[i], camera);

        axis[i] = transformer.perspective(axis[i], camera);

        axis[i] = transformer.toScreen(axis[i], image);
    }

    painter.drawLine(cube[0].x(), cube[0].z(), cube[1].x(), cube[1].z());
    painter.drawLine(cube[0].x(), cube[0].z(), cube[2].x(), cube[2].z());
    painter.drawLine(cube[0].x(), cube[0].z(), cube[4].x(), cube[4].z());
    painter.drawLine(cube[1].x(), cube[1].z(), cube[3].x(), cube[3].z());
    painter.drawLine(cube[1].x(), cube[1].z(), cube[5].x(), cube[5].z());
    painter.drawLine(cube[2].x(), cube[2].z(), cube[3].x(), cube[3].z());
    painter.drawLine(cube[2].x(), cube[2].z(), cube[6].x(), cube[6].z());
    painter.drawLine(cube[3].x(), cube[3].z(), cube[7].x(), cube[7].z());
    painter.drawLine(cube[4].x(), cube[4].z(), cube[5].x(), cube[5].z());
    painter.drawLine(cube[4].x(), cube[4].z(), cube[6].x(), cube[6].z());
    painter.drawLine(cube[5].x(), cube[5].z(), cube[7].x(), cube[7].z());
    painter.drawLine(cube[6].x(), cube[6].z(), cube[7].x(), cube[7].z());

    painter.setPen(QColor(255, 0, 0));
    painter.drawLine(axis[0].x(), axis[0].z(), axis[1].x(), axis[1].z());
    painter.setPen(QColor(0, 255, 0));
    painter.drawLine(axis[0].x(), axis[0].z(), axis[2].x(), axis[2].z());
    painter.setPen(QColor(0, 0, 255));
    painter.drawLine(axis[0].x(), axis[0].z(), axis[3].x(), axis[3].z());
}

void Model::addRotate(double alpha, double betta){
    transformer.changeRotate(alpha, betta);
}

void Model::setScaleItem(double scale, int i){
    items[i]->setScale(scale);
}

void Model::setXItem(double x, int i){
    items[i]->setX(x);
}

void Model::setYItem(double y, int i){
    items[i]->setY(y);
}

void Model::setZItem(double z, int i){
    items[i]->setZ(z);
}

void Model::set_nItem(int n, int i){
    items[i]->set_n(n);
}

void Model::set_kItem(int k, int i){
    items[i]->set_k(k);
}

void Model::setSpline(Spline spline, int i){
    *splines[i] = spline;
}

Spline Model::getSpline(int i){
    return *splines[i];
}
