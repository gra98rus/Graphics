#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);

    this->resize(sizeX + imgCoordX, sizeY + imgCoordY);

    image = QImage(sizeX, sizeY, QImage::Format_RGB32);
    image.fill(qRgb(255,255,255));

    model = Model();
    model.draw(image);

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start(10);

    splineWindow = new AddSpline(this);
    splineWindow->synModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        mousePressed = true;
        startCoursor = QVector2D(event->x(), event->y());
    }
}

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    image.fill(qRgb(255,255,255));

    model.draw(image);

    painter.drawImage(imgCoordX, imgCoordY, image);

}

void MainWindow::on_addSpline_clicked(){
    splineWindow->show();
}

void MainWindow::on_deleteItemButton_clicked()
{
    model.deleteLastItem();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    mousePressed = false;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if(mousePressed){
        double dx = (event->x() - startCoursor.x()) / 500;
        double dy = (event->y() - startCoursor.y()) / 500;
        model.addRotate(dy, dx);
        startCoursor = QVector2D(event->x(), event->y());

    }
}

void MainWindow::on_objectNumBox_valueChanged(int arg1){

}

void MainWindow::on_scaleBox_valueChanged(double arg1){
    model.setScaleItem(ui->scaleBox->value(), ui->objectNumBox->value());
}

void MainWindow::on_xBox_valueChanged(double arg1){
    model.setXItem(ui->xBox->value(), ui->objectNumBox->value());
}

void MainWindow::on_yBox_valueChanged(double arg1){
    model.setYItem(ui->yBox->value(), ui->objectNumBox->value());
}

void MainWindow::on_zBox_valueChanged(double arg1){
    model.setZItem(ui->zBox->value(), ui->objectNumBox->value());
}

void MainWindow::on_nBox_valueChanged(int arg1){
    model.set_nItem(ui->nBox->value(), ui->objectNumBox->value());
}

void MainWindow::on_kBox_valueChanged(int arg1){
    model.set_kItem(ui->kBox->value(), ui->objectNumBox->value());
}
