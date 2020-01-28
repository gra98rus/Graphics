#include "model.h"

Model::Model(){

}

Model::Model(QImage &beforeImg, QImage &afterImg){
    this->beforeImg = &beforeImg;
    this->afterImg = &afterImg;
}

void Model::toNegative(){
    filterProcessor.toNegative(*beforeImg, *afterImg);
    emit modelUpd();
}

void Model::toBW(){
    filterProcessor.toBW(*beforeImg, *afterImg);
    emit modelUpd();
}

void Model::afterToBefore(){
    *beforeImg = afterImg->copy();
    emit modelUpd();
}

void Model::beforeToAfter(){
    *afterImg = beforeImg->copy();
    emit modelUpd();
}

void Model::delineation(int shift){
    QVector<QVector<int>> matrix = {{-1, 0, 1},
                                    {-2, 0, 2},
                                    {-1, 0, 1}};
    QVector<QVector<int>> matrix1 = {{-1, -2, -1},
                                    {0, 0, 0},
                                    {1, 2, 1}};
    filterProcessor.sobolProcess(matrix, matrix1, 1, shift, *beforeImg, *afterImg);
    emit modelUpd();
}

void Model::blur(){
    QVector<QVector<int>> matrix = {{0, 1, 0},
                                   {1, 2, 1},
                                   {0, 1, 0}};
    filterProcessor.matrixProcess(matrix, 6, 0, *beforeImg, *afterImg);
    emit modelUpd();
}

void Model::sharpen(){
    QVector<QVector<int>> matrix = {{0, -1, 0},
                                   {-1, 5, -1},
                                   {0, -1, 0}};
    filterProcessor.matrixProcess(matrix, 1, 0, *beforeImg, *afterImg);
    emit modelUpd();
}

void Model::identic(){
    QVector<QVector<int>> matrix = {{0, 0, 0},
                                   {0, 1, 0},
                                   {0, 0, 0}};
    filterProcessor.matrixProcess(matrix, 1, 0, *beforeImg, *afterImg);
    emit modelUpd();
}

void Model::stamping(){
    QVector<QVector<int>> matrix = {{0, -1, 0},
                                   {1, 0, -1},
                                   {0, 1, 0}};
    filterProcessor.matrixProcess(matrix, 1, 128, *beforeImg, *afterImg);
    emit modelUpd();

}

void Model::aquarel(){
    QImage temp = *afterImg;
    filterProcessor.medianProcess(*beforeImg, temp);
    QVector<QVector<int>> matrix = {{0, -1, 0},
                                   {-1, 5, -1},
                                   {0, -1, 0}};
    filterProcessor.matrixProcess(matrix, 1, 0, temp, *afterImg);
    emit modelUpd();
}

void Model::gammaCorrection(double gamma){
    filterProcessor.gammaCorrection(gamma, *beforeImg, *afterImg);
    emit modelUpd();
}

void Model::openImage(QString filename){
    beforeImg->load(filename);
    afterImg->load(filename);
    emit modelUpd();
}

void Model::saveImage(QString filename){
    afterImg->save(filename);
}

void Model::customMatrixProcess(QVector<QVector<int>> matrix, int div, int shift){
    filterProcessor.matrixProcess(matrix, div, shift, *beforeImg, *afterImg);
    emit modelUpd();
}
