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
#include "math.h"
#include "model.h"
#include "scene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
     void paintEvent(QPaintEvent *);
     void mouseMoveEvent(QMouseEvent *event);
     void mousePressEvent(QMouseEvent *event);
     void addline(int x0, int x1, int y0, int y1);
     void updateImage();
     bool saveFile(QString filename);
     bool readFile(QString filename);
     bool createNewProject(QString filename);

private slots:
     void on_actionNew_file_triggered();

     void on_actionOpen_triggered();

     void on_actionAbout_triggered();

     void on_actionSave_triggered();

private:
    int sizeX = 2100;
    int sizeY = 1600;

    Ui::MainWindow *ui;
    QImage img;
    QPoint mPoint;
    QTimer timer;
    scene scene;


    PolyLine viewPL;


};
#endif // MAINWINDOW_H
