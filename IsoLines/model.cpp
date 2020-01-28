#include "model.h"

Model::Model()
{

}

Model::Model(double x0, double x1, double y0, double y1, int gridK, int gridM){
    this->x0 = x0;
    this->x1 = x1;
    this->y0 = y0;
    this->y1 = y1;
    this->gridK = gridK;
    this->gridM = gridM;
    map = Map(x0, x1, y0, y1, gridK, gridM);
    legend.setMinMax(y0, y1);
    QVector<double> minMaxF = function.fMinMax(x0, x1, y0, y1);
    legend.setMinMaxF(minMaxF[0], minMaxF[1]);
    legend.setLevels(10);
}

void Model::draw(QImage& image, QImage& legenda, QImage& legendText){
    map.drawFunc(image, function);
    map.drawFunc(legenda, legend);
    legend.drawText(legendText);
}

void Model::addIsoline(QVector<double> coord, bool funcOrLeg,  QImage& image, QImage& imageLegend){
    if(funcOrLeg)
        map.addIsoLine(coord, function);
    else
        map.addIsoLine(coord, legend);
    map.drawIsoLines(image, function);
    map.drawIsoLines(imageLegend, legend);
}

void Model::interpolation(QImage &image, QImage& legenda){
    map.drawInterpolation(image, function);
    map.drawInterpolation(legenda, legend);
}

void Model::dither(QImage &image, QImage& legenda){
    map.drawDither(image, function);
    map.drawDither(legenda, legend);
}

void Model::setGrid(QImage &image){
    map.drawGrid(image);
}

void Model::setIsolines(QImage &image, QImage& imageLegend){
    map.setIsolineLevels();
    map.drawIsoLines(image, function);
    map.drawIsoLines(imageLegend, legend);
}

QVector<double> Model::pixelToPoint(QPoint pixel, QImage &image){
    return map.pixelToPoint(pixel, image);
}

double Model::getFValue(QVector<double> coord){
    return function.f(coord);
}

double Model::getLegendValue(QVector<double> coord){
    return legend.f(coord);
}


void Model::readFile(QString filename){
    QFile file(filename);
    QVector<QColor> colors;
    QVector<double> list;
    if(!file.open(QIODevice::ReadWrite))
        return ;
    QTextStream stream(&file);
    QString line;
    line += stream.readLine();
    line += " ";
    line += stream.readLine();
    line += " ";
    line += stream.readLine();
    line += " ";
    line += stream.readLine();
    map = Map(parseArgs(line)[0], parseArgs(line)[1], parseArgs(line)[2], parseArgs(line)[3], parseArgs(line)[4], parseArgs(line)[5]);
    line = stream.readLine();
    map.setNumberOfLevels(line.toInt());

    while(!stream.atEnd()){
        line = stream.readLine();
        list = parseArgs(line);
        colors.append(QColor(list[0], list[1], list[2]));
    }

    map.setIsoColor(colors.last());
    colors.remove(colors.length() - 1);
    map.setColors(colors);

    file.close();
}

QVector<double> Model::parseArgs(QString line){
    QVector<double> vals;
    QStringList list = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    for(QString str: list)
        vals.append(str.toDouble());
    return vals;
}

void Model::setNumberOfLevels(int num){
    map.setNumberOfLevels(num);
}

void Model::setColors(QVector<QColor> col){
    map.setColors(col);
}

void Model::setIsoColor(QColor color){
    map.setIsoColor(color);
}
