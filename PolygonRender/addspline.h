#ifndef ADDSPLINE_H
#define ADDSPLINE_H

#include <QDialog>
#include <QImage>
#include "model.h"
#include <QTimer>
#include <QMouseEvent>
#include "spline.h"
#include <iostream>

namespace Ui {
class AddSpline;
}

class AddSpline : public QDialog
{
    Q_OBJECT

public:
    AddSpline(QWidget *parent = nullptr);

    void synModel(Model &model);

    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    ~AddSpline();

private slots:
    void on_buttonBox_accepted();

    void on_deleteButton_clicked();

    void on_changeSplineButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::AddSpline *ui;

    int sizeX = 1000;
    int sizeY = 800;

    int imgCoordX = 0;
    int imgCoordY =  80;

    QImage splineImage;
    Model * model;
    Spline spline;

    QTimer timer;

    bool mousePressed = false;
    int currentPoint = -1;

};

#endif // ADDSPLINE_H
