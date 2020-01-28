#include "polygon.h"

Polygon::Polygon(){

}

Polygon::Polygon(QVector<QPoint> points){
    this->coord = points;
}

void Polygon::addPoint(QPoint point){
    coord.append(point);
}

void Polygon::setWidth(int w){
    this->width = w;
}

void replace(int *x, int *y){
    int a = *x;
    *x = *y;
    *y = a;
}

void Polygon::drawLine(QPoint start, QPoint end, QImage& img){
    int x0 = start.x();
    int y0 = start.y();
    int x1 = end.x();
    int y1 = end.y();

    bool q = abs(y1-y0) > abs(x1-x0);
    if(q){
        replace(&x0, &y0);
        replace(&x1, &y1);
    }
    if(x0>x1){
        replace(&x0, &x1);
        replace(&y0, &y1);
    }
    int deltax = abs(x1 - x0);
    int deltay = abs(y1 - y0);
    int error = 0;
    int deltaerr = deltay;
    int y = y0;
    int diry = y1 - y0;
    if (diry > 0 )
         diry = 1;
    else
         diry = -1;
    for (int x = x0; x <= x1; x++){
        if (q) replace(&x, &y);
        img.setPixel(x, y, qRgb(0,0,0));
        if(width == 2){
            if (q)  img.setPixel(x+1, y, qRgb(0,0,0));
            else    img.setPixel(x, y+1, qRgb(0,0,0));
        }
        if(width == 3){
            if (q)  {
                img.setPixel(x+1, y, qRgb(0,0,0));
                img.setPixel(x-1, y, qRgb(0,0,0));
            }
            else    {
                img.setPixel(x, y+1, qRgb(0,0,0));
                img.setPixel(x, y-1, qRgb(0,0,0));
            }
        }
        if (q) replace(&x, &y);
        error = error + deltaerr;
        if (2 * error >= deltax){
            y = y + diry;
            error = error - deltax;
         }
    }
}

void Polygon::draw(QImage& img){
    if(coord.length() >= 1){
        for(int i = 0; i != coord.length() - 1; i++){
            drawLine(coord[i], coord[i + 1], img);
        }
        drawLine(coord[0], coord[coord.length() - 1], img);
    }
}

Polygon::~Polygon(){}

IFigure* Polygon::readFromFile(QTextStream &stream){
    QString line;
    line = stream.readLine();
    QStringList list = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    width = list[1].toInt();
       while(!stream.atEnd()){
           line = stream.readLine();
           if(line.isEmpty())
               break;
           coord.append(parseLine(line));
       }
       return this;
}

QPoint Polygon::parseLine(QString line){
    QStringList list = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    QPoint point(list[0].toInt(), list[1].toInt());
    return point;
}

void Polygon::writeToFile(QTextStream &stream){
    stream << "Polygon\n";
    stream << coord.length() << " " << width << '\n';
    for(QPoint point: coord)
        stream << point.x() << " " << point.y() << '\n';
    stream << '\n';
}

int Polygon::size(){
    return(coord.length());
}

void Polygon::clear(){
    coord.clear();
}

void Polygon::replaceLastPoint(QPoint point){
    coord.pop_back();
    coord.append(point);
}

void Polygon::delLastPoint(){
    coord.pop_back();
}
