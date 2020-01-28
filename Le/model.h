#ifndef MODEL_H
#define MODEL_H

#include <QGraphicsItem>
#include <QPainter>
#include <vector>
#include <QPixmap>
#include <QPainter>

class PolyLine
{
public:
    PolyLine();

    ~PolyLine();

    void addPoint(int x, int y);

    void deleteLastPoint();

    void clear();

    int size();

    void drawLine(QImage * img, int x0, int x1, int y0, int y1);

    void draw(QImage * img);

    int getLastXPoint();

    int getLastYPoint();

    void changeLastPoint(int x, int y);

    std::vector<int> getXCoordinaties();

    std::vector<int> getYCoordinaties();
private:
    std::vector<int> xcoord;
    std::vector<int> ycoord;

};

#endif // MODEL_H
