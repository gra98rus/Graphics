#include "function.h"

Function::Function()
{

}

double Function::fd(double x, double y){
    return (sin(x)+cos(y));
    //return (x*x+y*y);
}

double Function::f(QVector<double> coord){
    return (sin(coord[0])+cos(coord[1]));
    //return (coord[0]*coord[0]+coord[1]*coord[1]);
}


QVector<double> Function::fMinMax(double x0, double x1, double y0, double y1){
    double fmin = fd(x0, y0);
    double fmax = fd(x0, y0);
    double current;
    double xstep = (x1-x0)/100;
    double ystep = (y1-y0)/100;
    for(double i = x0; i < x1; i += xstep){
        for(double j = y0; j < y1; j += ystep){
            current = fd(i,j);
            if (current<fmin) fmin = current;
            if (current>fmax) fmax = current;
        }
    }
    QVector<double> extremums = {fmin, fmax};
    return extremums;
}
