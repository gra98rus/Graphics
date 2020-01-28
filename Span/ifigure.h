#ifndef IFIGURE_H
#define IFIGURE_H

#include <QImage>
#include <QTextStream>

class IFigure
{
public:
    IFigure();

    virtual void draw(QImage& image) = 0;

    virtual void writeToFile(QTextStream& stream) = 0;

    virtual IFigure* readFromFile(QTextStream& stream) = 0;

    virtual ~IFigure();
};


#endif // IFIGURE_H
