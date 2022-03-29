#ifndef NAVIGATIONALGORITHM_H
#define NAVIGATIONALGORITHM_H

#include <QObject>
#include <QGenericMatrix>

#include "stringtofloatmeasurements.h"

class NavigationAlgorithm : public QObject
{
    Q_OBJECT
public:
    NavigationAlgorithm();
    void input_ptrStF(StringToFloatMeasurements*);

public slots:
    void input_OmegaMatrix();
    void input_OmegaGMatrix();

signals:
    void signalCMatrixReady();

private:
    StringToFloatMeasurements *ptr_StringtoFloat;
    QGenericMatrix <3,3,double> С_Matrix;
    QGenericMatrix <3,3,double> OmegaMatrix;
};

#endif // NAVIGATIONALGORITHM_H
