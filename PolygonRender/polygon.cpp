#include "polygon.h"

Polygon::Polygon()
{

}

Polygon::Polygon(QVector4D a, QVector4D b, QVector4D c, QVector4D d)
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
}

void Polygon::draw(QPainter & painter, QColor color){
    QBrush br;
    br.setStyle(Qt::SolidPattern);
    br.setColor(color.rgb());
    painter.setBrush(br);

    QPainterPath path(QPointF(a.x(), a.z()));
    path.lineTo(d.x(), d.z());
    path.lineTo(c.x(), c.z());
    path.lineTo(b.x(), b.z());

    painter.fillPath(path, br);
}

