#include "legend.h"

Legend::Legend()
{

}

double Legend::f(QVector<double> coord){
   // std::cout<<minF<<std::endl;
    return minF+(maxF-minF)/(max-min)*(coord[1]-min);
}

void Legend::setMinMaxF(double minF, double maxF){
    //std::cout<<maxF<<std::endl;
    this->minF = minF;
    this->maxF = maxF;
}

void Legend::setMinMax(double min, double max){
    this->min = min;
    this->max = max;
}

void Legend::setLevels(int val){
    levels = val;
}

void Legend::drawText(QImage& image){

    QPainter painter(&image);
    painter.setPen(Qt::black);
    double value;
    for(int i = 10; i<image.height(); i+=image.height()/levels){
        value = maxF-(maxF-minF)*i/image.height();
        painter.drawText(QPoint(0, i), QString::number(value));
       // painter.drawText(QPoint(0, i), QString("%1").arg(value, 0, 'e', 2));
    }
}
