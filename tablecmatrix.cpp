#include "tablecmatrix.h"
#include "ui_tablecmatrix.h"

TableCMatrix::TableCMatrix(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableCMatrix)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(4);
    ui->tableWidget->setColumnCount(3);
}

TableCMatrix::~TableCMatrix()
{
    delete ui;
}

void TableCMatrix::input_C_Matrix(QGenericMatrix<3, 3, double> inp)
{
    С_Matrix = inp;
    for (int i=0; i < 3; i++)
        for (int j=0; j < 3; j++)
        {
            QString b = QString::number(inp(i,j));
            QTableWidgetItem *itm = new QTableWidgetItem(b);
            ui->tableWidget->setItem(i, j, itm);
        }
}

void TableCMatrix::input_angles(std::array<double, 3> inp)
{
    for (int i =0; i < 3; i++)
    {
        QString b = QString::number(inp[i]);
        QTableWidgetItem *itm = new QTableWidgetItem(b);
        ui->tableWidget->setItem(3, i, itm);
    }
}
