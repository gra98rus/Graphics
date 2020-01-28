#include "model.h"

PolyLine::PolyLine(){

}

PolyLine::~PolyLine(){

}

void PolyLine::addPoint(int x, int y){
    xcoord.push_back(x);
    ycoord.push_back(y);
}

void PolyLine::deleteLastPoint(){
    xcoord.pop_back();
    ycoord.pop_back();
}

void PolyLine::clear(){
    while(xcoord.size() != 0){
        xcoord.pop_back();
        ycoord.pop_back();
    }
}

int PolyLine::size(){
    return xcoord.size();
}

void replace(int *x, int *y){
    int a = *x;
    *x = *y;
    *y = a;
}

void PolyLine::drawLine(QImage * img, int x0, int x1, int y0, int y1){
    bool q = abs(y1-y0) > abs(x1-x0);
    if(q){
        replace(&x0, &y0);
        replace(&x1, &y1);
    }
    if(x0>x1){
        replace(&x0, &x1);
        replace(&y0, &y1);
    }
    int deltax = abs(x1 - x0);
    int deltay = abs(y1 - y0);
    int error = 0;
    int deltaerr = deltay;
    int y = y0;
    int diry = y1 - y0;
    if (diry > 0 )
         diry = 1;
    else
         diry = -1;
    for (int x = x0; x <= x1; x++){
        if (q) replace(&x, &y);
         img->setPixel(x, y, qRgb(0,0,0));
         if (q) replace(&x, &y);
         error = error + deltaerr;
         if (2 * error >= deltax){
             y = y + diry;
             error = error - deltax;
         }
    }
}

void PolyLine::draw(QImage *img){
    for(std::vector<int>::size_type i=1; i != xcoord.size(); i++){
        PolyLine::drawLine(img, xcoord[i-1], xcoord[i], ycoord[i-1], ycoord[i]);
    }
}

int PolyLine::getLastXPoint(){
    return xcoord[xcoord.size()-1];
}

int PolyLine::getLastYPoint(){
    return ycoord[ycoord.size()-1];
}

void PolyLine::changeLastPoint(int x, int y){
    xcoord.pop_back();
    ycoord.pop_back();
    xcoord.push_back(x);
    ycoord.push_back(y);
}

std::vector<int> PolyLine::getXCoordinaties(){
    return xcoord;
}

std::vector<int> PolyLine::getYCoordinaties(){
    return ycoord;
}
