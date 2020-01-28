#include "custommatrix.h"
#include "ui_custommatrix.h"

CustomMatrix::CustomMatrix(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomMatrix){
    ui->setupUi(this);
    matrix.resize(3);
    for(int i = 0; i != 3; i++)
        matrix[i].resize(3);
}

CustomMatrix::~CustomMatrix()
{
    delete ui;
}

void CustomMatrix::on_buttonBox_accepted()
{
    matrix[0][0] = ui->matrix00Box->value();
    matrix[0][1] = ui->matrix01Box->value();
    matrix[0][2] = ui->matrix02Box->value();
    matrix[1][0] = ui->matrix10Box->value();
    matrix[1][1] = ui->matrix11Box->value();
    matrix[1][2] = ui->matrix12Box->value();
    matrix[2][0] = ui->matrix20Box->value();
    matrix[2][1] = ui->matrix21Box->value();
    matrix[2][2] = ui->matrix22Box->value();

    div = ui->divBox->value();
    shift = ui->shiftBox->value();

    if(ui->autoCheckBox->isChecked()){
        div = 0;
        for(int i = 0; i<3; i++){
            for (int j = 0; j<3;j++) {
                div += matrix[i][j];
            }
        }
    }

    emit matrixUpd();
}

int CustomMatrix::getDiv(){
    return div;
}

QVector<QVector<int>> CustomMatrix::getMatrix(){
    return matrix;
}

int CustomMatrix::getShift(){
    return shift;
}
