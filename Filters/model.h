#ifndef MODEL_H
#define MODEL_H

#include <QImage>
#include "filterprocessor.h"

class Model: public QObject
{
    Q_OBJECT

private:
    FilterProcessor filterProcessor;

    QImage * beforeImg;
    QImage * afterImg;

public:
    Model();

    Model(QImage &beforeImg, QImage &afterImg);

    void toNegative();

    void toBW();

    void beforeToAfter();

    void afterToBefore();

    void delineation(int shift);

    void blur();

    void sharpen();

    void identic();

    void stamping();

    void aquarel();

    void gammaCorrection(double gamma);

    void openImage(QString filename);

    void saveImage(QString filename);

    void customMatrixProcess(QVector<QVector<int>> matrix, int div, int shift);

Q_SIGNALS:
    void modelUpd();
};

#endif // MODEL_H
