#include "scene.h"

scene::scene()
{

}

bool scene::saveFileAs(QString filename){
    currentFile = filename;
    QFile file(filename);
    if(!file.open(QIODevice::ReadWrite))
           return false;

    QTextStream stream(&file);

    stream << lines.size() << "\n";
    for(std::vector<int>::size_type j=0; j!=lines.size();j++ ){
        stream << "\n";
        stream << "Polyline\n";
        for(std::vector<int>::size_type i=0; i!=lines[j].size();i++){
            stream << lines[j].getXCoordinaties()[i] << " " << lines[j].getYCoordinaties()[i] << "\n";
        }
    }
    file.close();

    return true;
}

bool scene::saveFile(){
    QFile file(currentFile);

    if(!file.open(QIODevice::ReadWrite))
        return false;
    file.resize(0);
    QTextStream stream(&file);

    stream << lines.size() << "\n";
    for(std::vector<int>::size_type j=0; j!=lines.size();j++ ){
        stream << "\n";
        stream << "Polyline\n";
        for(std::vector<int>::size_type i=0; i!=lines[j].size();i++){
            stream << lines[j].getXCoordinaties()[i] << " " << lines[j].getYCoordinaties()[i] << "\n";
        }
    }
    file.close();

    return true;
}

bool scene::readFile(QString filename){
    currentFile = filename;
    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream stream(&file);
    QString line;
    int amount = file.readLine().toInt();
    file.readLine();

    while(!stream.atEnd()){
        line = stream.readLine();
        if(line == "Polyline"){
            while(!stream.atEnd()){
                line = stream.readLine();
                if(line.isEmpty()){
                    saveCurrentPL();
                    currentPol.clear();
                    break;
                }
                QStringList list = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
                int x = list[0].toInt();
                int y = list[1].toInt();
                currentPol.addPoint(x,y);
            }
        }
    }
    saveCurrentPL();
    file.close();
    return true;
}

bool scene::createNewProject(QString filename){
    currentFile = filename;

    QFile file(filename);
    file.open(QIODevice::ReadWrite);
    file.close();
    return true;
}

void scene::resetScene(){
    lines.clear();
    currentPol.clear();
}

bool scene::removeLastPoint(){

    if (currentPol.size() > 1){
        currentPol.deleteLastPoint();
        return true;
    }
    else if(currentPol.size() ==1 ){
        currentPol.clear();
    }
    else return false;
}

void scene::removeLastPolyline(){
    if ((currentPol.size() == 0) && (lines.size()!=0))
       lines.pop_back();
}

void scene::saveCurrentPL(){
    if(currentPol.size() > 1){
    lines.push_back(currentPol);
    currentPol.clear();
    }
}

int scene::sizeCurrentPL(){
    return currentPol.size();
}

int scene::amountLines(){
    return (int) lines.size();
}

PolyLine scene::getPolyline(int i){
    if(i <= lines.size())
    return lines[i];
}

void scene::draw(QImage *img){
    for(std::vector<int>::size_type i=0; i != lines.size(); i++){
        lines[i].draw(img);
    }
    if(currentPol.size() > 1)
        currentPol.draw(img);
}

int scene::getLastXPoint(){
    return currentPol.getLastXPoint();
}

int scene::getLastYPoint(){
    return currentPol.getLastYPoint();
}

void scene::addPointCurrentPL(int x, int y){
    currentPol.addPoint(x, y);
}

QString scene::getCurrentFile(){
    return currentFile;
}

void scene::changeCurrentFile(QString filename){
    currentFile = filename;
}
