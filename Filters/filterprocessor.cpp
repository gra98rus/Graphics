#include "filterprocessor.h"

FilterProcessor::FilterProcessor(){

}

void FilterProcessor::toBW(QImage &beforeImg, QImage &afterImg){
    QColor point;
    int color;
    for(int u = 0; u != beforeImg.width(); u++){
        for(int v = 0; v != beforeImg.height(); v++){
            point = beforeImg.pixel(u, v);
            color = 0.299 * point.red() + 0.587 * point.green() + 0.114 * point.blue();
            afterImg.setPixel(u, v, qRgb(color, color, color));
        }
    }
}

void FilterProcessor::toNegative(QImage &beforeImg, QImage &afterImg){
    QColor point;
    for (int i = 0; i < beforeImg.width(); i++){
        for (int j = 0; j < beforeImg.height(); j++){
            point = beforeImg.pixel(i, j);

            afterImg.setPixel(i, j, qRgb(255 - point.red(), 255 - point.green(), 255 - point.blue()));
        }
    }
}

void FilterProcessor::sobolProcess(QVector<QVector<int>> matrix, QVector<QVector<int>> matrix1, int div, int shift, QImage &beforeImg, QImage &afterImg){
    double r, g, b;
    double r1, g1, b1;
    int x, y;
    for(int v = 0; v != beforeImg.height(); v++){
       for(int u = 0; u != beforeImg.width(); u++){
            r = 0;
            g = 0;
            b = 0;
            r1 = 0;
            g1 = 0;
            b1 = 0;
            for(int i = 0; i != matrix.length(); i++){
                for(int j = 0; j != matrix[i].length(); j++){

                    x = (u - 1 + j);
                    y = (v - 1 + i);

                    x = x < 0 ? 0 : x;
                    y = y < 0 ? 0 : y;

                    x = x >= beforeImg.width() ? beforeImg.width() - 1 : x;
                    y = y >= beforeImg.height() ? beforeImg.height() - 1 : y;

                    r += matrix[i][j] * qRed(beforeImg.pixel(x, y));
                    g += matrix[i][j] * qGreen(beforeImg.pixel(x, y));
                    b += matrix[i][j] * qBlue(beforeImg.pixel(x, y));

                    r1 += matrix1[i][j] * qRed(beforeImg.pixel(x, y));
                    g1 += matrix1[i][j] * qGreen(beforeImg.pixel(x, y));
                    b1 += matrix1[i][j] * qBlue(beforeImg.pixel(x, y));
                }
            }

            r = sqrt(r*r+r1*r1);
            g = sqrt(g*g+g1*g1);
            b = sqrt(b*b+b1*b1);


            r = r / div + shift;
            g = g / div + shift;
            b = b / div + shift;
            r = r > 255 ? 255 : r;
            g = g > 255 ? 255 : g;
            b = b > 255 ? 255 : b;

            r = r < 0 ? 0 : r;
            g = g < 0 ? 0 : g;
            b = b < 0 ? 0 : b;


            if(r+g+b < 255*3/2)
                afterImg.setPixel(u, v, qRgb(0, 0, 0));
            else
                afterImg.setPixel(u, v, qRgb(255, 255, 255));
        }
    }
}

void FilterProcessor::matrixProcess(QVector<QVector<int>> matrix, int div, int shift, QImage &beforeImg, QImage &afterImg){
    double r, g, b;
    int x, y;
    for(int v = 0; v != beforeImg.height(); v++){
       for(int u = 0; u != beforeImg.width(); u++){
            r = 0;
            g = 0;
            b = 0;
            for(int i = 0; i != matrix.length(); i++){
                for(int j = 0; j != matrix[i].length(); j++){
                    x = (u - 1 + j);
                    y = (v - 1 + i);

                    x = x < 0 ? 0 : x;
                    y = y < 0 ? 0 : y;

                    x = x >= beforeImg.width() ? beforeImg.width() - 1 : x;
                    y = y >= beforeImg.height() ? beforeImg.height() - 1 : y;

                    r += matrix[i][j] * qRed(beforeImg.pixel(x, y));
                    g += matrix[i][j] * qGreen(beforeImg.pixel(x, y));
                    b += matrix[i][j] * qBlue(beforeImg.pixel(x, y));
                }
            }

            r = r / div + shift;
            g = g / div + shift;
            b = b / div + shift;
            r = r > 255 ? 255 : r;
            g = g > 255 ? 255 : g;
            b = b > 255 ? 255 : b;

            r = r < 0 ? 0 : r;
            g = g < 0 ? 0 : g;
            b = b < 0 ? 0 : b;

            afterImg.setPixel(u, v, qRgb(r, g, b));
        }
    }
}

void FilterProcessor::medianProcess(QImage &beforeImg, QImage &afterImg){
    QVector<int> pixColorsR;
    QVector<int> pixColorsG;
    QVector<int> pixColorsB;
    for(int v = 2; v < beforeImg.height() - 2; v++){
        for(int u = 2; u < beforeImg.width() - 2; u++){
            for(int j = -2; j < 3; j++){
                for(int i = -2; i < 3; i++){
                    pixColorsR.append(qRed(beforeImg.pixel(u + i, v + j)));
                    pixColorsG.append(qGreen(beforeImg.pixel(u + i, v + j)));
                    pixColorsB.append(qBlue(beforeImg.pixel(u + i, v + j)));
                }
            }
            std::sort(pixColorsR.begin(), pixColorsR.end());
            std::sort(pixColorsG.begin(), pixColorsG.end());
            std::sort(pixColorsB.begin(), pixColorsB.end());

            afterImg.setPixel(u, v, qRgb(pixColorsR[12], pixColorsG[12], pixColorsB[12]));
            pixColorsR.clear();
            pixColorsG.clear();
            pixColorsB.clear();
        }
    }
}

void FilterProcessor::gammaCorrection(double gamma, QImage &beforeImg, QImage &afterImg){
    QColor color;
    double r, g, b;
    for (int i = 0; i < beforeImg.width(); i++){
        for(int j = 0; j < beforeImg.height(); j++){

            color = beforeImg.pixel(i, j);

            r = pow(color.red() / 255.0, gamma);
            g = pow(color.green() / 255.0, gamma);
            b = pow(color.blue() / 255.0, gamma);

            r = r > 1 ? 255 : r * 255;
            g = g > 1 ? 255 : g * 255;
            b = b > 1 ? 255 : b * 255;

            afterImg.setPixel(i, j, qRgb(r, g, b));
        }
    }
}
