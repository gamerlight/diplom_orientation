#ifndef ORIENTATIONALGORITHM_H
#define ORIENTATIONALGORITHM_H

#include <QObject>
#include <QGenericMatrix>

#include "stringtofloatmeasurements.h"

class OrientationAlgorithm : public QObject
{
    Q_OBJECT
public:
    OrientationAlgorithm();
    void input_ptrStF(StringToFloatMeasurements*);
    void input_psi(double);
    QGenericMatrix <3,3,double> getC_Matrix();
    void input_OmegaMatrix();

public slots:
    void input_OmegaMatrix(std::array<double, 3>);
    void input_OmegaGMatrix(QGenericMatrix <3,3,double>);
    virtual void calculate_C_Matrix();
    void calucaltePsiThetaGamma();
    void block_process();

signals:
    void signalC_MatrixReady(QGenericMatrix <3,3,double> sig_matrix);
    void signalAnglesReady(std::array<double, 3> sig_Ang);
    void signalStartCMatrix();

protected:
    StringToFloatMeasurements *ptr_StringtoFloat;
    QGenericMatrix <3,3,double> Сc_Matrix;
    QGenericMatrix <3,3,double> OmegaMatrix;
    QGenericMatrix <3,3,double> OmegaGMatrix;
    double psi;
    double theta;
    double gamma;
    void correction_C_matrix();
};

#endif // ORIENTATIONALGORITHM_H
