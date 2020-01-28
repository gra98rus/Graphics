#ifndef IFUNCTION_H
#define IFUNCTION_H

#include <QVector>

class IFunction
{
public:
    IFunction();

    virtual double f(QVector<double> coord) = 0;

};

#endif // IFUNCTION_H
