#include "map.h"

Map::Map(){}

Map::Map(double x0, double x1, double y0, double y1, int gridK, int gridM)
{
    this->x0 = x0;
    this->x1 = x1;
    this->y0 = y0;
    this->y1 = y1;
    this->gridK = gridK;
    this->gridM = gridM;
    levelNum = 10;
    colors = {QColor(0, 6, 65), QColor(1, 18, 119), QColor(0, 81, 255), QColor(0, 117, 255), QColor(70, 250, 119), QColor(149, 250, 52), QColor(255, 171, 51), QColor(255, 136, 51), QColor(255, 75, 0), QColor(255, 48, 0)};
    isoColor = QColor(255, 255, 255);
}

void Map::drawFunc(QImage &image, IFunction& f){
    QVector<double> extremums = Function::fMinMax(x0, x1, y0, y1);
    double minF = extremums[0];
    double maxF = extremums[1];
    double colorStep = (maxF-minF)/levelNum;

    for(int x = 0; x < image.width(); x++){
        for(int y = 0; y < image.height(); y++){
            double value = f.f(pixelToPoint(QPoint(x, y), image));
            double colorLevel = minF;
            for(int level = 0; level < levelNum; level++){
                if(value<=minF){
                    image.setPixel(x, y, colors[0].rgb());
                    break;
                }
                if ((value>=colorLevel) && (value<=colorLevel+colorStep)) {
                    image.setPixel(x, y, colors[level].rgb());
                    break;
                }
                colorLevel+=colorStep;
                image.setPixel(x, y, colors[level].rgb());
                }
            }
        }


    setIsolineLevels();
}

void Map::drawIsoLines(QImage &image, IFunction& f){
    QVector<QPoint> points;
    QPainter painter(&image);
    painter.setPen(isoColor);

    int gridStepX = image.width()/gridK;
    int gridStepY = image.height()/gridM;

    double f1, f2, f3, f4;
    for(double isoline: isolineLevels){
        for(int u = 0; u < image.width(); u += gridStepX){
            for(int v = 0; v < image.height(); v += gridStepY){
                points.clear();
                f1 = f.f(pixelToPoint(QPoint(u,v), image));
                f2 = f.f(pixelToPoint(QPoint(u+gridStepX,v), image));
                f3 = f.f(pixelToPoint(QPoint(u,v+gridStepY), image));
                f4 = f.f(pixelToPoint(QPoint(u+gridStepX,v+gridStepY), image));
                if((isoline >= f1 && isoline < f2) || (isoline <= f1 && isoline > f2))
                    points.append(QPoint(u + gridStepX * (isoline - f1) / (f2 - f1), v));
                if((isoline >= f2 && isoline < f4) || (isoline <= f2 && isoline > f4))
                    points.append(QPoint(u + gridStepX, v + gridStepY * (isoline - f2) / (f4 - f2)));
                if((isoline > f1 && isoline <= f3) || (isoline < f1 && isoline >= f3))
                    points.append(QPoint(u, v + gridStepY * (isoline - f1) / (f3 - f1)));
                if((isoline > f3 && isoline <= f4) || (isoline < f3 && isoline >= f4))
                    points.append(QPoint(u + gridStepX * (isoline - f3) / (f4 - f3), v + gridStepY));

                if(points.length() == 4){
                double f5 = (f1 + f2 + f3 + f4) / 4.;
                if((isoline > f1 && isoline <= f5) || (isoline < f1 && isoline >= f5))
                    std::swap(points[1], points[2]);
                painter.drawLine(points[0], points[1]);
                painter.drawLine(points[2], points[3]);
                }
                if(points.length() == 2)
                    painter.drawLine(points[0], points[1]);
            }
        }
    }
}

void Map::setIsolineLevels(){
    isolineLevels.clear();
    QVector<double> extremums = Function::fMinMax(x0, x1, y0, y1);
    double min = extremums[0];
    double max = extremums[1];
    double step = (max - min) / levelNum;
    for(int i = 0; i < levelNum; i++)
        isolineLevels.append(min + i * step);
}

void Map::addIsoLine(QVector<double> coord, IFunction& f){
    isolineLevels.clear();
    isolineLevels.append(f.f(coord));
}

QVector<double> Map::pixelToPoint(QPoint pixel, QImage& image){
    QVector<double> temp;
    temp.append(x0+pixel.x()*(x1-x0)/image.width());
    temp.append(y0+(image.height()-pixel.y())*(y1-y0)/image.height());
    return temp;
}

void Map::drawInterpolation(QImage &image, IFunction& f){
    QColor pixColor;
    double valueF;
    int isolineLevelNum;
    int r, g, b;
    for(int u = 0; u<image.width(); u++){
        for(int v = 0; v<image.height(); v++){
            pixColor = image.pixel(u, v);
            valueF = f.f(pixelToPoint(QPoint(u, v), image));
            isolineLevelNum = getIsolineLevelNum(valueF);
            if(isolineLevels.length() - 1 > isolineLevelNum){
            r = (int)qRed(colors[isolineLevelNum].rgb()) + (valueF - isolineLevels[isolineLevelNum]) * ( qRed(colors[isolineLevelNum + 1].rgb()) - qRed(colors[isolineLevelNum].rgb()) ) / (isolineLevels[isolineLevelNum + 1] - isolineLevels[isolineLevelNum]);
            g = (int)qGreen(colors[isolineLevelNum].rgb()) + (valueF - isolineLevels[isolineLevelNum]) * ( qGreen(colors[isolineLevelNum + 1].rgb()) - qGreen(colors[isolineLevelNum].rgb()) ) / (isolineLevels[isolineLevelNum + 1] - isolineLevels[isolineLevelNum]);
            b = (int)qBlue(colors[isolineLevelNum].rgb()) + (valueF - isolineLevels[isolineLevelNum]) * ( qBlue(colors[isolineLevelNum + 1].rgb()) - qBlue(colors[isolineLevelNum].rgb()) ) / (isolineLevels[isolineLevelNum + 1] - isolineLevels[isolineLevelNum]);
            image.setPixel(u, v, qRgb(r, g, b));
            }
        }
    }
}

int Map::getIsolineLevelNum(double val){
    for(int i = 0; i < isolineLevels.length() - 1; i++){
        if(val >= isolineLevels[i] && val < isolineLevels[i + 1])
            return i;
    }
    return isolineLevels.length() - 1;
}

void Map::drawDither(QImage &image, IFunction& f){
    drawInterpolation(image, f);
    double minError = 884;
    double currentError;
    int nearestColor;
    double er, eg, eb;
    double temper, tempeg, tempeb;
    QColor pixColor;
    for(int v = 0; v<image.height()-1; v++){
        for(int u = 1; u<image.width()-1; u++){
            pixColor = image.pixel(u, v);
            for(int i = 0; i < levelNum; i++){
                temper = pixColor.red()-colors[i].red();
                tempeg = pixColor.green()-colors[i].green();
                tempeb = pixColor.blue()-colors[i].blue();
                currentError = sqrt(temper*temper+tempeg*tempeg+tempeb*tempeb);
                if(currentError<minError){
                    er = temper;
                    eg = tempeg;
                    eb = tempeb;
                    minError = currentError;
                    nearestColor = i;
                }

            }
            image.setPixel(u, v, colors[nearestColor].rgb());
            minError = 884;

            er /= 16;
            eg /= 16;
            eb /= 16;

            int k = 3;
            addError(u-1, v+1, er, eg, eb, k, image);
            addError(u, v+1, er, eg, eb, k, image);
            addError(u+1, v+1, er, eg, eb, k, image);
            addError(u+1, v, er, eg, eb, k, image);

        }
    }
}

void Map::addError(int u, int v, double eR, double eG, double eB, int k, QImage &image){
    QColor pixColor = image.pixel(u, v);
    int r, g, b;
    r = (k*eR+pixColor.red())>255 ? 255 : (k*eR+pixColor.red());
    r = (k*eR+pixColor.red())<0 ? 0 : (k*eR+pixColor.red());
    g = (k*eG+pixColor.green())>255 ? 255 : (k*eG+pixColor.green());
    g = (k*eG+pixColor.green())<0 ? 0 : (k*eG+pixColor.green());
    b = (k*eB+pixColor.blue())>255 ? 255 : (k*eB+pixColor.blue());
    b = (k*eB+pixColor.blue())<0 ? 0 : (k*eB+pixColor.blue());
    image.setPixel(u, v, qRgb(r, g, b));
}

void Map::drawGrid(QImage &image){
    QVector<QPoint> points;
    QPainter painter(&image);
    painter.setPen(Qt::black);

    int step_u = image.width() / gridK < 1 ? 1 : image.width() / gridK;
    int step_v = image.height() / gridM < 1 ? 1: image.height() / gridM;

    for(int u = 0; u <= image.width(); u += step_u)
            painter.drawLine(u, 0, u, image.height());
    for(int v = 0; v <= image.height(); v += step_v)
        painter.drawLine(0, v, image.width(), v);
}

void Map::setNumberOfLevels(int num){
    levelNum = num;
}

void Map::setColors(QVector<QColor> col){
    colors = col;
}

void Map::setIsoColor(QColor color){
    isoColor = color;
}
