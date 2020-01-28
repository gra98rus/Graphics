#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMouseTracking(true);
    centralWidget()->setMouseTracking(true);

    this->resize(2100,1600);
    //this->setFixedSize(2100,1600);

    img = QImage(sizeX, sizeY, QImage::Format_RGB32);
    for (int i = 0; i < sizeX; i++){
        for (int j=0;j<sizeY;j++) {
            img.setPixel(i,j, qRgb(255,255,255));
        }
    }

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start(5);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
    MainWindow::updateImage();
    QPainter painter(this);
    painter.drawImage(0, 98, img);
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        int x = event->x();
        int y = event->y();
        scene.addPointCurrentPL(x, y-98);
        if(viewPL.size() != 0){
            viewPL.clear();
            viewPL.addPoint(x, y-98);
            viewPL.addPoint(x, y-98);
        }
        else{
            viewPL.addPoint(x, y-98);
            viewPL.addPoint(x, y-98);
        }
    }
    else if(event->button() == Qt::RightButton){
        scene.saveCurrentPL();
        viewPL.clear();

    }
    else if(event->button() == Qt::MidButton){
        scene.saveCurrentPL();
        if (scene.amountLines() != 0){
            scene.removeLastPolyline();
        viewPL.clear();
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if(viewPL.size()>0)
    viewPL.changeLastPoint(event->x(), event->y()-98);
}

void MainWindow::updateImage(){
    for (int i = 0; i < sizeX; i++)
        for (int j = 0; j < sizeY; j++)
            img.setPixel(i,j, qRgb(255,255,255));
    scene.draw(&img);
    if(viewPL.size() == 2)
        viewPL.draw(&img);
}

void MainWindow::on_actionNew_file_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "D:\Graphics\LeTask",
                                                    tr("*.le"));
    if(!filename.isEmpty())
        scene.resetScene();
        scene.saveFileAs(filename);
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open"),
                                                    "D:\Graphics\LeTask",
                                                    "*.le");
    if(!filename.isEmpty())
        scene.resetScene();
        scene.readFile(filename);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, "About", "This is programm can draw polylines");

}

void MainWindow::on_actionSave_triggered()
{
    if(scene.getCurrentFile().length() == 0){
    QString filename = QFileDialog::getSaveFileName(this, tr("Open"),
                                                    "D:\Graphics\LeTask",
                                                    "*.le");
    scene.changeCurrentFile(filename);
    }
    scene.saveFile();
}
