#ifndef FILL_H
#define FILL_H

#include "ifigure.h"
#include <stack>
#include <iostream>

#define WIDTH 3072
#define HEIGHT 2048

class Fill: public IFigure
{
public:
    Fill();

    Fill(QPoint seed, QRgb color, int connectivity);

    void draw(QImage& image);

    void writeToFile(QTextStream &stream);

    IFigure* readFromFile(QTextStream &stream);

    void setSeed(QPoint point);

    void setColor(QRgb col);

    void setConnectivity(int value);

private:

    QPoint seed;
    QRgb color;
    int connectivity;

    void spanAlg(QImage& image);

    void identifySpan(QPoint point, QRgb oldColor, std::stack<QLine>& spans, QImage& image);

    void drawSpan(QLine& span, QImage& image);

    void identifyNeighbours(QLine& currentSpan, std::stack<QLine>& spans, QRgb oldColor, QImage& image);

    void parseLine(QString line);

};

#endif // FILL_H
