#ifndef SCENE_H
#define SCENE_H

#include "model.h"
#include <QVector>
#include <QFile>
#include <iostream>
#include <QTextStream>
#include <QPixmap>
#include <QPainter>

class scene
{
public:
    scene();

    bool saveFile();

    bool saveFileAs(QString filename);

    bool readFile(QString filename);

    bool createNewProject(QString filename);

    void resetScene();

    void removeLastPolyline();

    bool removeLastPoint();

    void saveCurrentPL();

    int sizeCurrentPL();

    int amountLines();

    PolyLine getPolyline(int i);

    void draw(QImage * img);

    int getLastXPoint();

    int getLastYPoint();

    void addPointCurrentPL(int x, int y);

    QString getCurrentFile();

    void changeCurrentFile(QString filename);

private:
    std::vector <PolyLine> lines;
    PolyLine currentPol;
    QString currentFile;

};

#endif // SCENE_H
