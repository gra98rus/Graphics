#include "addspline.h"
#include "ui_AddSpline.h"

AddSpline::AddSpline(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSpline){
    ui->setupUi(this);

    this->resize(sizeX + imgCoordX, sizeY + imgCoordY);

    splineImage = QImage(sizeX, sizeY, QImage::Format_RGB32);
    splineImage.fill(qRgb(255,255,255));

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start(10);

    spline = Spline();
}

AddSpline::~AddSpline(){
    delete ui;
}

void AddSpline::synModel(Model &model){
    this->model = &model;
}

void AddSpline::mousePressEvent(QMouseEvent *event){
    if((event->x()-imgCoordX < 0) || (event->y()-imgCoordY < 0))
            return;

    if(event->button() == Qt::LeftButton){
        int x = event->x() - imgCoordX;
        int y = event->y() - imgCoordY;
        spline.addControlPoint(x, y);
    }
    if(event->button() == Qt::RightButton){
        int x = event->x() - imgCoordX;
        int y = event->y() - imgCoordY;
        QVector<QVector2D> points = spline.getControlPoints();
        for(int i = 0; i < points.length(); i++){
            if(points[i].distanceToPoint(QVector2D(x, y)) < 25){
                currentPoint = i;
                spline.changeControlPoint(currentPoint, QVector2D(x, y));
                std::cout<<i<<"   "<<points[i].x()<<"   "<<points[i].y()<<std::endl;
            }
        }
    }
}

void AddSpline::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    splineImage.fill(qRgb(255,255,255));
    for(int i = 0; i < splineImage.height(); i++){
        splineImage.setPixel(splineImage.width()/2, i, qRgb(0, 255, 0));
    }
    for(int i = 0; i < splineImage.width(); i++){
        splineImage.setPixel(i, splineImage.height()/2, qRgb(0, 255, 0));
    }
    spline.draw(1, splineImage);

    painter.drawImage(imgCoordX, imgCoordY, splineImage);
}

void AddSpline::on_buttonBox_accepted(){
    model->addSplineForItem(spline, ui->xBox->value(), ui->yBox->value(), ui->zBox->value(), ui->scaleBox->value());
    spline = Spline();

}

void AddSpline::on_deleteButton_clicked(){
    spline.deleteLastPoint();
}

void AddSpline::mouseReleaseEvent(QMouseEvent *event){
    int x = event->x() - imgCoordX;
    int y = event->y() - imgCoordY;
    spline.changeControlPoint(currentPoint, QVector2D(x, y));
    currentPoint = -1;
    mousePressed = false;
}

void AddSpline::mouseMoveEvent(QMouseEvent *event){
    spline.changeControlPoint(currentPoint, QVector2D(event->x() - imgCoordX, event->y() - imgCoordY));
}

void AddSpline::on_changeSplineButton_clicked()
{
    spline = model->getSpline(ui->splineNumBox->value());
}



void AddSpline::on_saveButton_clicked(){
    model->setSpline(spline, ui->splineNumBox->value());
    spline = Spline();
}
