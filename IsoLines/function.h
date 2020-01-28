#ifndef FUNCTION_H
#define FUNCTION_H

#include <QImage>
#include <iostream>
#include "ifunction.h"
#include "math.h"

class Function: public IFunction
{
public:
    Function();

    double static fd(double x, double y);

    double f(QVector<double> coord);

    //double static legenda(double x, double y);

    double static legenda(QVector<double> coord);

    QVector<double> static fMinMax(double x0, double x1, double y0, double y1);

private:

};

#endif // FUNCTION_H
