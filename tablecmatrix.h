#ifndef TABLECMATRIX_H
#define TABLECMATRIX_H

#include <QDialog>
#include <QGenericMatrix>
#include <QString>

namespace Ui {
class TableCMatrix;
}

class TableCMatrix : public QDialog
{
    Q_OBJECT

public:
    explicit TableCMatrix(QWidget *parent = nullptr);
    ~TableCMatrix();
public slots:
    void input_C_Matrix(QGenericMatrix <3,3,double>);
    void input_angles(std::array<double, 3>);

private:
    Ui::TableCMatrix *ui;
    QGenericMatrix <3,3,double> С_Matrix;
};

#endif // TABLECMATRIX_H
