#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = Model(-2, 2, -2, 2, 100, 100);

    //readFile("D:/Graphics/IsoLines/build-IsoLines-Desktop_x86_windows_msys_pe_64bit-Debug/setup.is");

    this->setMouseTracking(true);
    centralWidget()->setMouseTracking(true);

    this->resize(2250,1500);

    image = QImage(sizeX, sizeY, QImage::Format_RGB32);
    image.fill(qRgb(255,255,255));

    imageLegend = QImage(legendSizeX, legendSizeY, QImage::Format_RGB32);
    imageLegend.fill(qRgb(255,255,255));

    imageLegendText = QImage(legendTextSizeX, legendTextSizeY, QImage::Format_ARGB32);
    imageLegendText.fill(qRgba(0, 0, 0, 0));

    imageGrid = QImage(sizeX, sizeY, QImage::Format_ARGB32);
    imageGrid.fill(qRgba(0, 0, 0, 0));

    imageDynamicMap = QImage(sizeX, sizeY, QImage::Format_ARGB32);
    imageDynamicMap.fill(qRgba(0, 0, 0, 0));

    imageDynamicLeg = QImage(legendSizeX, legendSizeY, QImage::Format_ARGB32);
    imageDynamicLeg.fill(qRgba(0, 0, 0, 0));

    window = new Dialog(this);

    model.draw(image, imageLegend, imageLegendText);

    connect(window, SIGNAL(updatedParams()), this, SLOT(setParams()));
    connect(this, SIGNAL(upd()), this, SLOT(update()));

    isIsolines = false;
    isGrid = false;
    wasPressed = false;
    isDithering = false;
    isInterpolated = false;
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    imageDynamicMap.fill(qRgba(0, 0, 0, 0));
    imageDynamicLeg.fill(qRgba(0, 0, 0, 0));
    if(event->x()<image.width()&&event->y()>imgCoordY){
        QVector<double> coord = model.pixelToPoint(QPoint(event->x(), event->y()-imgCoordY), image);
        model.addIsoline(coord, true, imageDynamicMap, imageDynamicLeg);
    }
    if(event->x()>image.width()+50){
        QVector<double> coord = model.pixelToPoint(QPoint(event->x()-(image.width()+50), event->y()-imgCoordY), imageGrid);
        model.addIsoline(coord, false, imageDynamicMap, imageDynamicLeg);
    }
    wasPressed = true;
    emit upd();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    wasPressed = false;
    imageDynamicMap.fill(qRgba(0, 0, 0, 0));
    imageDynamicLeg.fill(qRgba(0, 0, 0, 0));
    emit upd();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if(event->x()<image.width()&&event->y()>imgCoordY){
        QVector<double> coord = model.pixelToPoint(QPoint(event->x(), event->y()-imgCoordY), image);
        double fVal = model.getFValue(coord);
        ui->statusbar->showMessage("x: " + QString::number(coord[0]) + " y: " + QString::number(coord[1]) + " | f(x, y)= " + QString::number(fVal));
        if(wasPressed){
            imageDynamicMap.fill(qRgba(0, 0, 0, 0));
            imageDynamicLeg.fill(qRgba(0, 0, 0, 0));
            model.addIsoline(coord, true, imageDynamicMap, imageDynamicLeg);
            emit upd();
        }
    }
    if(event->x()>image.width()+50){
        QVector<double> coord = model.pixelToPoint(QPoint(event->x()-(image.width()+50), event->y()-imgCoordY), imageGrid);
        double legendVal = model.getLegendValue(coord);
        ui->statusbar->showMessage("x: " + QString::number(coord[0]) + " y: " + QString::number(coord[1]) + " | f(x, y)= " + QString::number(legendVal));
        if(wasPressed){
            imageDynamicMap.fill(qRgba(0, 0, 0, 0));
            imageDynamicLeg.fill(qRgba(0, 0, 0, 0));
            model.addIsoline(coord, false, imageDynamicMap, imageDynamicLeg);
            emit upd();
        }
    }
}

void MainWindow::resizeEvent(QResizeEvent *event){
    image = QImage(this->width() - 250, this->height() - imgCoordY, QImage::Format_RGB32);
    imageLegend = QImage(legendSizeX, this->height() - imgCoordY, QImage::Format_RGB32);
    imageLegendText = QImage(legendTextSizeX, this->height() - imgCoordY, QImage::Format_ARGB32);
    imageGrid = QImage(this->width() - 250, this->height() - imgCoordY, QImage::Format_ARGB32);
    imageDynamicMap = QImage(this->width() - 250, this->height() - imgCoordY, QImage::Format_ARGB32);
    imageDynamicLeg = QImage(legendSizeX, this->height() - imgCoordY, QImage::Format_ARGB32);

    imageLegendText.fill(qRgba(0, 0, 0, 0));

    model.draw(image, imageLegend, imageLegendText);

    if(isIsolines){
        model.setIsolines(imageGrid, imageDynamicLeg);
    }
    if(isGrid)
        model.setGrid(imageGrid);
    if(isInterpolated)
        model.interpolation(image, imageLegend);
    if(isDithering)
        model.dither(image, imageLegend);


    emit upd();
}

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawImage(imgCoordX, imgCoordY, image);
    painter.drawImage(image.width()+50, imgCoordY, imageLegend);
    painter.drawImage(image.width()+imageLegend.width()+50, imgCoordY, imageLegendText);
    painter.drawImage(imgCoordX, imgCoordY, imageGrid);
    painter.drawImage(image.width()+50, imgCoordY, imageDynamicLeg);
    painter.drawImage(imgCoordX, imgCoordY, imageDynamicMap);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_interpolationButton_clicked()
{
    isInterpolated = true;
    isDithering = false;
    model.interpolation(image, imageLegend);
    this->repaint();

}

void MainWindow::on_ditherButton_clicked()
{
    isInterpolated = false;
    isDithering = true;
    model.dither(image, imageLegend);
    this->repaint();
}

void MainWindow::on_settingButton_clicked()
{
    window->show();
}

void MainWindow::setParams(){
    QVector<double> parametrs;
    parametrs.append(window->getMinX());
    parametrs.append(window->getMaxX());
    parametrs.append(window->getMinY());
    parametrs.append(window->getMaxY());
    parametrs.append(window->getGridK());
    parametrs.append(window->getGridM());
    model= Model(parametrs[0], parametrs[1], parametrs[2], parametrs[3], parametrs[4], parametrs[5]);
    imageLegendText.fill(qRgba(0, 0, 0, 0));

    model.draw(image, imageLegend, imageLegendText);

    isGrid = false;
    isIsolines = false;
    emit upd();
}

void MainWindow::on_isolinesButton_clicked()
{
    if(isIsolines){
        imageDynamicLeg.fill(qRgba(0, 0, 0, 0));
        imageGrid.fill(qRgba(0, 0, 0, 0));
        if(isGrid)
            model.setGrid(imageGrid);

        isIsolines = false;
    }
    else{
        model.setIsolines(imageGrid, imageDynamicLeg);
        isIsolines = true;
    }
    emit upd();
}

void MainWindow::on_gridButton_clicked()
{
    if(isGrid){
        imageGrid.fill(qRgba(0, 0, 0, 0));
        if(isIsolines){
            model.setIsolines(imageGrid, imageDynamicLeg);
        }
        isGrid = false;
    }
    else{
        model.setGrid(imageGrid);
        isGrid = true;
    }
    emit upd();
}

void MainWindow::readFile(QString filename){
    QFile file(filename);
    QVector<QColor> colors;
    QVector<double> list;
    if(!file.open(QIODevice::ReadWrite))
        return ;
    QTextStream stream(&file);
    QString line;
    line += stream.readLine();
    line += " ";
    line += stream.readLine();
    line += " ";
    line += stream.readLine();
    line += " ";
    line += stream.readLine();
    model = Model(parseArgs(line)[2], parseArgs(line)[0], parseArgs(line)[3], parseArgs(line)[1], parseArgs(line)[4], parseArgs(line)[5]);

    //mo = Map(parseArgs(line)[0], parseArgs(line)[1], parseArgs(line)[2], parseArgs(line)[3], parseArgs(line)[4], parseArgs(line)[5]);
    line = stream.readLine();
    model.setNumberOfLevels(line.toInt());

    while(!stream.atEnd()){
        line = stream.readLine();
        list = parseArgs(line);
        colors.append(QColor(list[0], list[1], list[2]));
    }

    model.setIsoColor(colors.last());
    colors.remove(colors.length() - 1);
    model.setColors(colors);

    file.close();
}

QVector<double> MainWindow::parseArgs(QString line){
    QVector<double> vals;
    QStringList list = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    for(QString str: list)
        vals.append(str.toDouble());
    return vals;
}
