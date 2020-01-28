#include "fill.h"

Fill::Fill(){}

Fill::Fill(QPoint seed, QRgb color, int connectivity){
    this->seed = seed;
    this->color = color;
    this->connectivity = connectivity;
}

void Fill::draw(QImage &image){
    spanAlg(image);
}

void Fill::writeToFile(QTextStream &stream){
    stream << "Fill\n";
    QColor qcolor(color);
    int red = qcolor.red();
    int green = qcolor.green();
    int blue = qcolor.blue();
    stream << seed.x() << " " << seed.y() << " " << red << " " << green << " " << blue << " " << connectivity << '\n';
    stream << '\n';
}

IFigure* Fill::readFromFile(QTextStream &stream){
    QVector<int> args;
    QString line;
    while(!stream.atEnd()){
        line = stream.readLine();
        if(line.isEmpty())
            break;
        parseLine(line);
    }
    return this;
}

void Fill::parseLine(QString line){
    QStringList list = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    seed = QPoint(list[0].toInt(), list[1].toInt());
    color = qRgb(list[2].toInt(), list[3].toInt(), list[4].toInt());
    connectivity = list[5].toInt();
}

void Fill::setSeed(QPoint point){
    seed = point;
}

void Fill::setColor(QRgb col){
    color = col;
}

void Fill::setConnectivity(int value){
    connectivity = value;
}

void Fill::spanAlg(QImage &image){
    QRgb oldColor = image.pixel(seed.x(), seed.y());
    if(oldColor == color)
        return;
    std::stack<QLine> spans;
    QLine currentSpan;
    identifySpan(seed, oldColor, spans, image);
    while(!spans.empty()){
        currentSpan = spans.top();
        drawSpan(currentSpan, image);
        spans.pop();
        identifyNeighbours(currentSpan, spans, oldColor, image);
    }
}

void Fill::identifySpan(QPoint point, QRgb oldColor, std::stack<QLine> &spans, QImage &image){
    int leftEdge = 0;
    int rightEdge = WIDTH-1;

    for(int x = point.x(); x>=0; x--){
        if (image.pixel(x, point.y()) != oldColor){
            leftEdge = x + 1;
            break;
        }
    }
    for(int x = point.x(); x<=WIDTH; x++){
        if(x == WIDTH){
            rightEdge = x - 1 ;
            break;
        }
        if ((image.pixel(x, point.y()) != oldColor)){
            rightEdge = x - 1 ;
            break;
        }
    }
    spans.push(*(new QLine(leftEdge, point.y(), rightEdge, point.y())));
}

void Fill::drawSpan(QLine& span, QImage &image){
    for(int x = span.x1(); x <= span.x2(); x++){
        QPoint point(x, span.y1());
        image.setPixel(point, color);
    }
}

void Fill::identifyNeighbours(QLine& span, std::stack<QLine>& spans, QRgb oldColor, QImage& image){
    for(int x = span.x1(), y = span.y1() + 1; x < span.x2();){
        if(y >= HEIGHT)
            break;
        if(image.pixel(x, y) == oldColor){
            QPoint point(x,y);
            identifySpan(point, oldColor, spans, image);
            x = spans.top().x2();
        }
        x++;
        if(x >= span.x2())
            break;
    }
    for(int x = span.x1(), y = span.y1() - 1; x < span.x2();){
        if(y < 0)
            break;
        if(image.pixel(x, y) == oldColor){
            QPoint point(x,y);
            identifySpan(point, oldColor, spans, image);
            x = spans.top().x2();
        }
        x++;
        if(x > span.x2())
            break;
    }

    if(connectivity == 4) return;

    if((span.x2() < WIDTH - 1) && (span.y1() < HEIGHT - 1)){
        if(image.pixel(span.x2() + 1, span.y1() + 1) == oldColor){
            QPoint point(span.x2() + 1,span.y1() + 1);
            identifySpan(point, oldColor, spans, image);
        }
    }

    if((span.x1() > 0) && (span.y1() < HEIGHT - 1)){
        if(image.pixel(span.x1() - 1, span.y1() + 1) == oldColor){
            QPoint point(span.x2() - 1,span.y1() + 1);
            identifySpan(point, oldColor, spans, image);
        }
    }

    if((span.x1() > 0) && (span.y1() > 0)){
        if(image.pixel(span.x1() - 1, span.y1() - 1) == oldColor){
            QPoint point(span.x2() - 1,span.y1() - 1);
            identifySpan(point, oldColor, spans, image);
        }
    }

    if((span.x2() < WIDTH - 1) && (span.y1() > 0)){
        if(image.pixel(span.x2() + 1, span.y1() - 1) == oldColor){
            QPoint point(span.x2() + 1,span.y1() - 1);
            identifySpan(point, oldColor, spans, image);
        }
    }
}
