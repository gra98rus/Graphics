#ifndef CUSTOMMATRIX_H
#define CUSTOMMATRIX_H

#include <QDialog>
#include <QVector>

namespace Ui {
class CustomMatrix;
}

class CustomMatrix : public QDialog
{
    Q_OBJECT

public:
    CustomMatrix(QWidget *parent = nullptr);

    QVector<QVector<int>> getMatrix();

    int getDiv();

    int getShift();

    ~CustomMatrix();

Q_SIGNALS:
    void matrixUpd();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CustomMatrix *ui;
    QVector<QVector<int>> matrix;
    int div;
    int shift;
};

#endif // CUSTOMMATRIX_H
