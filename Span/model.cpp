#include "model.h"

model::model(){
    currentCircle = Circle(QPoint(0,0), 0);
    currentPolygon.setWidth(1);
}

bool model::saveFileAs(QString filename){
    currentFile = filename;
    QFile file(filename);
    if(!file.open(QIODevice::ReadWrite))
           return false;

    QTextStream stream(&file);

    for(int i = 0; i != elements.length(); i++)
            elements[i]->writeToFile(stream);
    file.close();
    return true;
}

bool model::saveFile(){
    QFile file(currentFile);

    if(!file.open(QIODevice::ReadWrite))
        return false;
    file.resize(0);
    QTextStream stream(&file);

    for(int i = 0; i != elements.length(); i++)
        elements[i]->writeToFile(stream);
    file.close();
    return true;
}

bool model::readFile(QString filename){
    currentFile = filename;
    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream stream(&file);
    QString line;
        while(!stream.atEnd()){
            line = stream.readLine();
            if(line == "Polygon"){
                elements.append((new Polygon())->readFromFile(stream));
            }
            else if(line == "Circle")
                elements.append((new Circle())->readFromFile(stream));
            else if(line == "Fill")
                elements.append((new Fill())->readFromFile(stream));
        }
    file.close();


    return true;
}

void model::open(QString filename, QImage& image){
    readFile(filename);
    for(int i = 0; i != elements.length(); i++)
        elements[i]->draw(image);
}

bool model::createNewProject(QString filename){
    currentFile = filename;
    QFile file(filename);
    file.open(QIODevice::ReadWrite);
    file.close();
    return true;
}

void model::resetScene(){
    elements.clear();
}


bool model::saveCurrentPolygon(){
    if(currentPolygon.size() >= 1){
        elements.append(new Polygon(currentPolygon));
        currentPolygon.clear();
    }
}

QString model::getCurrentFile(){
    return currentFile;
}

void model::changeCurrentFile(QString filename){
    currentFile = filename;
}


Polygon model::getCurrentPolygon(){
    return currentPolygon;
}

Circle model::getCurrentCircle(){
    return currentCircle;
}

void model::addCurrentPolygonPoint(QPoint point){
    currentPolygon.addPoint(point);
}

void model::addCurrentCircle(QPoint center, int radius){
    currentCircle.setCenter(center);
    currentCircle.setRadius(radius);
}

void model::changeRadCurrentCircleByPoint(QPoint point){
    int rad = static_cast<int>(sqrt(pow(point.x() - currentCircle.getCenter().x(), 2) + pow(point.y() - currentCircle.getCenter().y(), 2)));
    currentCircle.setRadius(rad);
}

void model::saveCurrentCircle(){
    elements.append(new Circle(currentCircle));
    currentCircle.clear();
}

void model::changeCurrentPointPolygon(QPoint point){
    if(currentPolygon.size() != 0){
        if(currentPolygon.size() == 1){
            currentPolygon.addPoint(point);
        }
        currentPolygon.replaceLastPoint(point);
    }
}

void model::delCurrentPointPolygon(){
    if(currentPolygon.size() != 0)
        currentPolygon.delLastPoint();
}

void model::addFill(QPoint point, QRgb color, int connectivity, QImage &image){
    Fill* tempFill = new Fill(point, color, connectivity);
    elements.append(tempFill);
    tempFill->draw(image);

}

void model::changeCurrentPolugonWidth(int width){
    currentPolygon.setWidth(width);
}

model::~model(){}
