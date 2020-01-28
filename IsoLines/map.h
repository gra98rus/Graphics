#ifndef MAP_H
#define MAP_H

#include <QPainter>
#include <iostream>
#include <QVector>
#include "function.h"

class Map
{
public:
    Map();

    Map(double x0, double x1, double y0, double y1, int gridK, int gridM);

    void drawFunc(QImage& image, IFunction& f);

    void drawIsoLines(QImage& image, IFunction& f);

    void setIsolineLevels();

    void addIsoLine(QVector<double> coord, IFunction& f);

    void drawInterpolation(QImage& image, IFunction& f);

    int getIsolineLevelNum(double val);

    void drawDither(QImage& image, IFunction& f);

    void drawGrid(QImage& image);

    QVector<double> pixelToPoint(QPoint pixel, QImage& image);

    void setNumberOfLevels(int num);

    void setColors(QVector<QColor> col);

    void setIsoColor(QColor color);


private:
    double x0, x1, y0, y1;
    int gridK, gridM;
    int levelNum;
    QVector<QColor> colors;
    QVector<double> isolineLevels;
    QVector<double> usersIsoline;
    QVector<QPoint> points;
    QVector<double> lenghtColor;
    QColor isoColor;

    void addError(int u, int v, double eR, double eG, double eB, int kf, QImage& image);
};

#endif // MAP_H
