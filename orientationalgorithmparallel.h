#ifndef ORIENTATIONALGORITHMPARALLEL_H
#define ORIENTATIONALGORITHMPARALLEL_H

#include "orientationalgorithm.h"

#include <omp.h>

class OrientationAlgorithmParallel : public OrientationAlgorithm
{
public:
    OrientationAlgorithmParallel();

    // OrientationAlgorithm interface
public slots:
    virtual void calculate_C_Matrix() override;

private:
    QGenericMatrix <3,3,double> multiplyMatrix(QGenericMatrix <3,3,double>, QGenericMatrix <3,3,double>);
    QGenericMatrix <3,3,double> multiplyMatrix(double, QGenericMatrix <3,3,double>);
    QGenericMatrix <3,3,double> addMatrix(QGenericMatrix <3,3,double>, QGenericMatrix <3,3,double>);
    QGenericMatrix <3,3,double> subtractMatrix(QGenericMatrix <3,3,double>, QGenericMatrix <3,3,double>);
};

#endif // ORIENTATIONALGORITHMPARALLEL_H
