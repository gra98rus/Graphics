#ifndef LEGEND_H
#define LEGEND_H

#include "function.h"
#include "ifunction.h"
#include <QVector>
#include <QPainter>
#include <QString>

class Legend: public IFunction
{
public:
    Legend();

    double f(QVector<double> coord);

    void setMinMaxF(double minF, double maxF);

    void setMinMax(double min, double max);

    void setLevels(int val);

    void drawText(QImage& image);
private:
    double min, max;
    double minF, maxF;
    int levels;
};

#endif // LEGEND_H
