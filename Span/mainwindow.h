#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QTextStream>
#include <QMainWindow>
#include <QPixmap>
#include <QPainter>
#include <QCursor>
#include <QMouseEvent>
#include <QTimer>
#include <QFile>
#include <fstream>
#include <QFileDialog>
#include <QMessageBox>
#include <QColorDialog>
#include <QScrollArea>
#include <QLabel>
#include <QScrollBar>
#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

     void paintEvent(QPaintEvent *);

     void mouseMoveEvent(QMouseEvent *event);

     void mousePressEvent(QMouseEvent *event);

     void mouseReleaseEvent(QMouseEvent *event);

     void addline(int x0, int x1, int y0, int y1);

     bool saveFile(QString filename);

     bool readFile(QString filename);

     bool createNewProject(QString filename);

     void updateCurrentImage();

private slots:
     void on_actionOpen_triggered();

     void on_actionAbout_triggered();

     void on_actionSave_triggered();

     void on_circleButton_toggled(bool checked);

     void on_polygonButton_toggled(bool checked);

     void on_fillButton_toggled(bool checked);

     void on_colorButton_clicked();

     void on_fill8Button_toggled(bool checked);

     void on_actionNew_File_triggered();

     void on_widthBox_valueChanged(int arg1);

private:
    int sizeX = 3072;
    int sizeY = 2048;

    int imgCoordX = 0;
    int imgCoordY = 180;

    bool mousePressed = false;

    Ui::MainWindow *ui;
    QImage img;
    QImage currentImage;
    QPoint mPoint;
    QTimer timer;
    model model;
    QRgb color = qRgb(0,0,0);
    QScrollArea *scrollArea;
    QLabel *label;
;

};
#endif // MAINWINDOW_H
