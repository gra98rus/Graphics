#ifndef POLYGON_H
#define POLYGON_H

#include <QVector4D>
#include <QImage>
#include <QBrush>
#include <QPainter>
#include <QColor>

class Polygon
{
public:
    Polygon();

    Polygon(QVector4D a, QVector4D b, QVector4D c, QVector4D d);

    void draw(QPainter & painter, QColor color);

    QVector4D a, b, c, d;
    QVector4D normal;
};

#endif // POLYGON_H
