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
    this->setFixedSize(2100,1600);

    scrollArea = new QScrollArea(this);
    label = new QLabel(this);
    label->setScaledContents(true);
    label->adjustSize();
    scrollArea->setWidget(label);
    scrollArea->move(imgCoordX, imgCoordY);
    scrollArea->setFixedSize(2100 - imgCoordX, 1600 - imgCoordY);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setMouseTracking(true);
    label->setMouseTracking(true);
    label->adjustSize();

    img = QImage(sizeX, sizeY, QImage::Format_RGB32);
    img.fill(qRgb(255,255,255));

    currentImage = QImage(sizeX, sizeY, QImage::Format_RGB32);
    currentImage.fill(qRgb(255,255,255));

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start(1);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
    updateCurrentImage();
    QPainter painter(this);
    label->setPixmap(QPixmap::fromImage(currentImage));
    label->adjustSize();
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if((event->x()-imgCoordX < 0) || (event->y()-imgCoordY < 0))
            return;
    QPoint point(event->x()-imgCoordX + scrollArea->horizontalScrollBar()->value(), event->y()-imgCoordY + scrollArea->verticalScrollBar()->value());
     if(event->button() == Qt::LeftButton){
        if(ui->polygonButton->isChecked()){
            model.addCurrentPolygonPoint(point);
         }
        if(ui->fillButton->isChecked()){
            model.addFill(point, color, 4, img);
         }
        if(ui->fill8Button->isChecked()){
            model.addFill(point, color, 8, img);
         }
        else if(ui->circleButton->isChecked()){
            mousePressed = true;
            model.addCurrentCircle(point, 1);
        }
    }
    else if(event->button() == Qt::RightButton){
        if(ui->polygonButton->isChecked()){
            model.delCurrentPointPolygon();
            model.getCurrentPolygon().draw(img);
            model.saveCurrentPolygon();
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    if(ui->circleButton->isChecked()){
        model.getCurrentCircle().draw(img);
        model.saveCurrentCircle();
        mousePressed = false;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    QPoint point(event->x()-imgCoordX + scrollArea->horizontalScrollBar()->value(), event->y()-imgCoordY + scrollArea->verticalScrollBar()->value());
    if(ui->circleButton->isChecked() && mousePressed){
       model.changeRadCurrentCircleByPoint(point);
    }
    else if (ui->polygonButton->isChecked()){
        model.changeCurrentPointPolygon(point);
    }
}

void MainWindow::updateCurrentImage(){
    currentImage = img;
    model.getCurrentCircle().draw(currentImage);
    model.getCurrentPolygon().draw(currentImage);
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open"),
                                                    "D:\Graphics\Span",
                                                    "*.spn");
    if(!filename.isEmpty())
        model.resetScene();
        img.fill(qRgb(255,255,255));
        model.open(filename, img);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, "About", "This is programm can draw polylines");

}

void MainWindow::on_actionSave_triggered()
{
    if(model.getCurrentFile().length() == 0){
    QString filename = QFileDialog::getSaveFileName(this, tr("Open"),
                                                    "D:\Graphics\Span",
                                                    "*.spn");
    model.changeCurrentFile(filename);
    }
    model.saveFile();
}

void MainWindow::on_circleButton_toggled(bool checked)
{
    if(checked){
        ui->circleButton->setChecked(checked);
        ui->polygonButton->setChecked(!checked);
        ui->fillButton->setChecked(!checked);
        ui->fill8Button->setChecked(!checked);
    }
}

void MainWindow::on_polygonButton_toggled(bool checked)
{
    if(checked){
        ui->circleButton->setChecked(!checked);
        ui->polygonButton->setChecked(checked);
        ui->fillButton->setChecked(!checked);
        ui->fill8Button->setChecked(!checked);
    }
}

void MainWindow::on_fillButton_toggled(bool checked)
{
    if(checked){
        ui->circleButton->setChecked(!checked);
        ui->polygonButton->setChecked(!checked);
        ui->fillButton->setChecked(checked);
        ui->fill8Button->setChecked(!checked);
    }
}

void MainWindow::on_colorButton_clicked()
{
    QColor color = QColorDialog::getColor(color, this);
    if ( color.isValid() ){
     this->color = color.rgb();
    }
}

void MainWindow::on_fill8Button_toggled(bool checked)
{
    if(checked){
        ui->circleButton->setChecked(!checked);
        ui->polygonButton->setChecked(!checked);
        ui->fillButton->setChecked(!checked);
        ui->fill8Button->setChecked(checked);
    }
}

void MainWindow::on_actionNew_File_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "D:\Graphics\Span",
                                                    tr("*.spn"));
    std::cout<<filename.toStdString()<<std::endl;
    if(!filename.isEmpty())
        model.resetScene();
        img.fill(qRgb(255,255,255));
        model.saveFileAs(filename);
}

void MainWindow::on_widthBox_valueChanged(int arg1)
{
    model.changeCurrentPolugonWidth(arg1);

}
