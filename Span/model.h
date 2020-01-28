#ifndef MODEL_H
#define MODEL_H

#include <QVector>
#include <QFile>
#include <iostream>
#include <QTextStream>
#include <QPixmap>
#include <QPainter>
#include <math.h>

#include "polygon.h"
#include "circle.h"
#include "fill.h"
#include "ifigure.h"

class model
{
public:
    model();

    bool saveFile();

    bool saveFileAs(QString filename);

    void open(QString filename, QImage& image);

    bool createNewProject(QString filename);

    void resetScene();

    bool saveCurrentPolygon();

    int sizeCurrentPL();

    QString getCurrentFile();

    void changeCurrentFile(QString filename);

    Polygon getCurrentPolygon();

    Circle getCurrentCircle();

    void addCurrentPolygonPoint(QPoint point);

    void changeCurrentPolugonWidth(int width);

    void addCurrentCircle(QPoint center, int radius);

    void changeRadCurrentCircleByPoint(QPoint point);

    void saveCurrentCircle();

    void changeCurrentPointPolygon(QPoint point);

    void delCurrentPointPolygon();

    void addFill(QPoint point, QRgb color, int connectivity, QImage& image);

    ~model();

private:

    QVector<IFigure*> elements;
    Circle currentCircle;
    Polygon currentPolygon;
    QString currentFile;

    bool readFile(QString filename);
};

#endif // MODEL_H
