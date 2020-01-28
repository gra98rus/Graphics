#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <QVector4D>

class LightSource
{
public:
    LightSource();

    LightSource(QVector4D position);

    QVector4D position;
private:
};

#endif // LIGHTSOURCE_H
