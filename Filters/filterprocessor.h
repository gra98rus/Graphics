#ifndef FILTERPROCESSOR_H
#define FILTERPROCESSOR_H

#include <QImage>
#include "math.h"

class FilterProcessor
{
public:
    FilterProcessor();

    void toBW(QImage& beforeImg, QImage& afterImg);

    void toNegative(QImage& beforeImg, QImage& afterImg);

    void sobolProcess(QVector<QVector<int>> matrix, QVector<QVector<int>> matrix1, int div, int shift, QImage& beforeImg, QImage& afterImg);

    void matrixProcess(QVector<QVector<int>> matrix, int div, int shift, QImage& beforeImg, QImage& afterImg);

    void medianProcess(QImage& beforeImg, QImage& afterImg);

    void gammaCorrection(double gamma, QImage& beforeImg, QImage& afterImg);
};

#endif // FILTERPROCESSOR_H
