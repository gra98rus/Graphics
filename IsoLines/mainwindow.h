#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QScrollArea>
#include <QLabel>
#include <QScrollBar>
#include <QPainter>
#include <iostream>
#include <QMouseEvent>
#include "model.h"
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void resizeEvent(QResizeEvent *event);

    void readFile(QString filename);

    QVector<double> parseArgs(QString line);

    ~MainWindow();

Q_SIGNALS:
    void upd();

public slots:
    void setParams();

private slots:
    void on_interpolationButton_clicked();

    void on_ditherButton_clicked();

    void on_settingButton_clicked();

    void on_isolinesButton_clicked();

    void on_gridButton_clicked();

private:
    int sizeX = 2000;
    int sizeY = 1400;

    int legendSizeX = 100;
    int legendSizeY = 1400;

    int legendTextSizeX = 100;
    int legendTextSizeY = 1400;

    int imgCoordX = 0;
    int imgCoordY =  80;


    Dialog *window;

    bool mousePressed = false;

    Ui::MainWindow *ui;

    QImage image;
    QImage imageLegend;
    QImage imageLegendText;
    QImage imageGrid;
    QImage imageDynamicLeg;
    QImage imageDynamicMap;

    Model model;
    QRgb color = qRgb(0,0,0);

    bool isIsolines;
    bool isGrid;
    bool wasPressed;
    bool isDithering;
    bool isInterpolated;
};
#endif // MAINWINDOW_H
