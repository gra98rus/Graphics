#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QFileDialog>
#include "model.h"
#include "custommatrix.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);

    void resizeEvent(QResizeEvent *event);

    ~MainWindow();

public slots:
    void customMatrix();

private slots:
    void on_BWButton_clicked();

    void on_negativeButton_clicked();

    void on_beforeToAfterButton_clicked();

    void on_afterToBeforeButton_clicked();

    void on_delineationButton_clicked();

    void on_blurButton_clicked();

    void on_sharpenButton_clicked();

    void on_delineationSlider_sliderReleased();

    void on_identicButton_clicked();

    void on_stampingButton_clicked();

    void on_aquarelButton_clicked();

    void on_gammaButton_clicked();

    void on_gammaSpinBox_valueChanged(double arg1);

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_customDialogButton_clicked();

private:
    Ui::MainWindow *ui;
    Model * model;

    int sizeX = 2500;
    int sizeY = 1500;

    int imgCoordX = 0;
    int imgCoordY =  200;

    QImage beforeBackgroundImg;
    QImage afterBackgroundImg;
    QImage beforeImg;
    QImage afterImg;

    CustomMatrix *matrixWindow;
};
#endif // MAINWINDOW_H
