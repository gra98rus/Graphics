#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);

    this->setMouseTracking(true);
    centralWidget()->setMouseTracking(true);

    this->resize(sizeX,sizeY);

    beforeBackgroundImg = QImage(this->width() / 2 - 10, this->height() - imgCoordY, QImage::Format_RGB32);
    beforeBackgroundImg.fill(qRgb(255,255,255));

    afterBackgroundImg = QImage(this->width() / 2 - 10, this->height() - imgCoordY, QImage::Format_RGB32);
    afterBackgroundImg.fill(qRgb(255,255,255));


//    beforeImg = QImage("D:/Graphics/Filters/test.png");
//    afterImg = QImage("D:/Graphics/Filters/test.png");

//    beforeImg = QImage("D:/Graphics/Filters/lenna.jpg");
//    afterImg = QImage("D:/Graphics/Filters/lenna.jpg");

    beforeImg = QImage("D:/Graphics/Filters/2114.jpg");
    afterImg = QImage("D:/Graphics/Filters/2114.jpg");

    beforeImg.setPixel(beforeImg.width() / 2, beforeImg.height() / 2, qRgb(255, 255, 255));
    afterImg.setPixel(afterImg.width() / 2, afterImg.height() / 2, qRgb(255, 255, 255));

    model = new Model(beforeImg, afterImg);

    matrixWindow = new CustomMatrix(this);

    connect(model, SIGNAL(modelUpd()), this, SLOT(update()));
    connect(matrixWindow, SIGNAL(matrixUpd()), this, SLOT(customMatrix()));
}

void MainWindow::paintEvent(QPaintEvent *event){

    QPainter pt1(&beforeBackgroundImg);
    QPainter pt2(&afterBackgroundImg);

    pt1.drawImage(beforeBackgroundImg.width() / 2 - beforeImg.width() / 2, beforeBackgroundImg.height() / 2 - beforeImg.height() / 2, beforeImg);
    pt2.drawImage(afterBackgroundImg.width() / 2 - afterImg.width() / 2, afterBackgroundImg.height() / 2 - afterImg.height() / 2, afterImg);

    QPainter painter(this);

    painter.drawImage(0, imgCoordY, beforeBackgroundImg);
    painter.drawImage(beforeBackgroundImg.width() + 10, imgCoordY, afterBackgroundImg);
}

void MainWindow::resizeEvent(QResizeEvent *event){
    beforeBackgroundImg = QImage(this->width() / 2 - 10, this->height() - imgCoordY, QImage::Format_RGB32);
    afterBackgroundImg = QImage(this->width() / 2 - 10, this->height() - imgCoordY, QImage::Format_RGB32);
    beforeBackgroundImg.fill(qRgb(255, 255, 255));
    afterBackgroundImg.fill(qRgb(255, 255, 255));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_BWButton_clicked(){
    model->toBW();
}

void MainWindow::on_negativeButton_clicked(){
    model->toNegative();
}

void MainWindow::on_beforeToAfterButton_clicked(){
    model->beforeToAfter();
}

void MainWindow::on_afterToBeforeButton_clicked(){
    model->afterToBefore();
}

void MainWindow::on_delineationButton_clicked(){
    model->delineation(ui->delineationSlider->value());
}

void MainWindow::on_blurButton_clicked(){
    model->blur();
}

void MainWindow::on_sharpenButton_clicked(){
    model->sharpen();
}

void MainWindow::on_delineationSlider_sliderReleased(){
    model->delineation(ui->delineationSlider->value());
}

void MainWindow::on_identicButton_clicked(){
    model->identic();
}

void MainWindow::on_stampingButton_clicked(){
    model->stamping();
}

void MainWindow::on_aquarelButton_clicked(){
    model->aquarel();
}

void MainWindow::on_gammaButton_clicked(){
    model->gammaCorrection(ui->gammaSpinBox->value());
}

void MainWindow::on_gammaSpinBox_valueChanged(double arg1){
    model->gammaCorrection(arg1);
}

void MainWindow::on_actionOpen_triggered(){
    QString filename = QFileDialog::getOpenFileName(this, tr("Open"),
                                                                "D:\Graphics\Filters",
                                                                tr("*.bmp *.png *.gif *.jpg"));
    beforeBackgroundImg.fill(qRgb(255,255,255));
    afterBackgroundImg.fill(qRgb(255,255,255));
    model->openImage(filename);
}

void MainWindow::on_actionSave_triggered(){
    QString filename = QFileDialog::getSaveFileName(this, tr("Save"),
                                                                "D:\Graphics\Filters",
                                                                tr("*.bmp *.png *.gif *.jpg"));
    model->saveImage(filename);
}

void MainWindow::customMatrix(){
    model->customMatrixProcess(matrixWindow->getMatrix(), matrixWindow->getDiv(), matrixWindow->getShift());
}

void MainWindow::on_customDialogButton_clicked(){
    matrixWindow->show();
}
