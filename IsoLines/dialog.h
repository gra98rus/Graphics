#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <iostream>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);

    double getMinY();

    double getMinX();

    double getMaxY();

    double getMaxX();

    double getGridK();

    double getGridM();

    ~Dialog();

Q_SIGNALS:
    void updatedParams();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialog *ui;
    double minY;
    double maxY;
    double minX;
    double maxX;
    int gridK;
    int gridM;

};

#endif // DIALOG_H
