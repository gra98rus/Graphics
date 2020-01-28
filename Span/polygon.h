#ifndef POLYGON_H
#define POLYGON_H

#include <QGraphicsItem>
#include <QPainter>
#include <vector>
#include <QPixmap>
#include <QPainter>
#include <QPoint>
#include <iostream>

#include "ifigure.h"

class Polygon: public IFigure
{
private:
    QVector<QPoint> coord;
    int width;

    QPoint parseLine(QString line);

public:
    Polygon();

    Polygon(QVector<QPoint> points);

    ~Polygon();

    void addPoint(QPoint point);

    void setWidth(int w);

    void draw(QImage& image);

    void drawLine(QPoint start, QPoint end, QImage& image);

    void writeToFile(QTextStream &stream);

    IFigure* readFromFile(QTextStream &stream);

    int size();

    void clear();

    void replaceLastPoint(QPoint point);

    void delLastPoint();
};

#endif // POLYGON_H
