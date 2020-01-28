#ifndef CIRCLE_H
#define CIRCLE_H

#include "ifigure.h"

class Circle: public IFigure
{
public:
    Circle();

    Circle(QPoint center, int radius);

    void setCenter(QPoint point);

    void setRadius(int rad);

    int getRadius();

    QPoint getCenter();

    void clear();

    void draw(QImage& image);

    void writeToFile(QTextStream &stream);

    IFigure* readFromFile(QTextStream &stream);
private:

    QPoint center;
    int radius;

    void parseLine(QString line);


};

#endif // CIRCLE_H
