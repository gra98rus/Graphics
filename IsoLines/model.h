#ifndef MODEL_H
#define MODEL_H

#include "function.h"
#include "map.h"
#include "legend.h"
#include <QImage>
#include <QTextStream>
#include <QFile>

class Model
{
public:
    Model();

    Model(double x0, double x1, double y0, double y1, int gridK, int gridM);

    void draw(QImage& image, QImage& legenda, QImage& legendText);

    void addIsoline(QVector<double> coord, bool funcOrLeg, QImage& image, QImage& legenda);

    void interpolation(QImage& image, QImage& legenda);

    void dither(QImage& image, QImage& legenda);

    void setGrid(QImage& image);

    void setIsolines(QImage& image, QImage& legenda);

    QVector<double> pixelToPoint(QPoint pixel, QImage& image);

    double getFValue(QVector<double> coord);

    double getLegendValue(QVector<double> coord);

    void readFile(QString filename);

    QVector<double> parseArgs(QString line);

    void setNumberOfLevels(int num);

    void setColors(QVector<QColor> col);

    void setIsoColor(QColor color);

private:
    Function function;
    double x0, x1, y0, y1;
    int gridK, gridM;
    Map map;
    Legend legend;
    IFunction* ifunc = &function;
    IFunction* ilegend = &legend;

};

#endif // MODEL_H
