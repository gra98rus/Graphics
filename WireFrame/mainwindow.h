#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include "model.h"
#include <QTimer>
#include <QMouseEvent>
#include <QKeyEvent>
#include "addspline.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);


    ~MainWindow();

private slots:
    void on_addSpline_clicked();

    void on_deleteItemButton_clicked();

    void on_objectNumBox_valueChanged(int arg1);

    void on_scaleBox_valueChanged(double arg1);

    void on_xBox_valueChanged(double arg1);

    void on_yBox_valueChanged(double arg1);

    void on_zBox_valueChanged(double arg1);

    void on_nBox_valueChanged(int arg1);

    void on_kBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;

    int sizeX = 2000;
    int sizeY = 1400;

    int imgCoordX = 0;
    int imgCoordY =  80;

    QImage image;
    QTimer timer;

    Model model;

    AddSpline * splineWindow;

    bool mousePressed = false;
    QVector2D startCoursor;
};
#endif // MAINWINDOW_H
