#include "circle.h"

Circle::Circle(){}

Circle::Circle(QPoint center, int radius){
    this->center = center;
    this->radius = radius;
}

void Circle::setCenter(QPoint point){
    center = point;
}

void Circle::setRadius(int rad){
    radius = rad;
}

QPoint Circle::getCenter(){
    return(center);
}

int Circle::getRadius(){
    return (radius);
}

void Circle::clear(){
    radius = -1;
}

void Circle::draw(QImage &image){
    if(radius != -1){
        int x1 = center.x();
        int y1 = center.y();
        int x = 0;
        int y = radius;
        int delta = 1 - 2 * radius;
        int error = 0;
        while (y >= 0){
            image.setPixel(x1 + x, y1 + y, qRgb(0, 0, 0));
            image.setPixel(x1 + x, y1 - y, qRgb(0, 0, 0));
            image.setPixel(x1 - x, y1 + y, qRgb(0, 0, 0));
            image.setPixel(x1 - x, y1 - y, qRgb(0, 0, 0));
            error = 2 * (delta + y) - 1;
            if ((delta < 0) && (error <= 0)){
                delta += 2 * ++x + 1;
                continue;
            }
            if ((delta > 0) && (error > 0)){
                delta -= 2 * --y + 1;
                continue;
            }
            delta += 2 * (++x - y--);
        }
    }
}

void Circle::writeToFile(QTextStream &stream){
    stream << "Circle\n";
    stream << center.x() << " " << center.y() << " " << radius << '\n';
    stream << '\n';
}

IFigure* Circle::readFromFile(QTextStream &stream){
    QVector<int> args;
    QString line;
    while(!stream.atEnd()){
        line = stream.readLine();
        if(line.isEmpty())
            break;
        parseLine(line);
    }
    return this;
}

void Circle::parseLine(QString line){
    QStringList list = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    center = QPoint(list[0].toInt(), list[1].toInt());
    radius = list[2].toInt();
}
