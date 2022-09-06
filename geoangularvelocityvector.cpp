#include "geoangularvelocityvector.h"
#include <QtMath>

GeoAngularVelocityVector::GeoAngularVelocityVector()
{

}

void GeoAngularVelocityVector::input_Phi(double inp_Phi)
{
    Phi = inp_Phi;
    emit signalStartCalculate();
}

void GeoAngularVelocityVector::input_diff_Lambda(double inp_diff_Lambda)
{
    diff_Lambda = inp_diff_Lambda;
}

void GeoAngularVelocityVector::input_diff_Phi(double inp_diff_Phi)
{
    diff_Phi = inp_diff_Phi;
}

void GeoAngularVelocityVector::calculate_OmegaGMatrix()
{
    std::array<double, 3> OmegaG;
    OmegaG[0] = (0.00007268518 + diff_Lambda) * qCos(Phi);
    OmegaG[1] = (0.00007268518 + diff_Lambda) * qSin(Phi);
    OmegaG[2] = -diff_Phi;
    OmegaGMatrix(0, 0) = 0;
    OmegaGMatrix(0, 1) = -OmegaG[2];
    OmegaGMatrix(0, 2) = OmegaG[1];
    OmegaGMatrix(1, 0) = OmegaG[2];
    OmegaGMatrix(1, 1) = 0;
    OmegaGMatrix(1, 2) = -OmegaG[0];
    OmegaGMatrix(2, 0) = -OmegaG[1];
    OmegaGMatrix(2, 1) = OmegaG[0];
    OmegaGMatrix(2, 2) = 0;
    emit signalOmegaGMatrix(OmegaGMatrix);
}

QGenericMatrix<3, 3, double> GeoAngularVelocityVector::get_OmegaGMatrix()
{
    return OmegaGMatrix;
}
