#include "navigationalgorithm.h"

#include <QtMath>

NavigationAlgorithm::NavigationAlgorithm()
{
    accel_array.fill(0);
}

void NavigationAlgorithm::input_Lambda(double inp_Lamda)
{
    Lambda = inp_Lamda;
}

void NavigationAlgorithm::input_Phi(double inp_Phi)
{
    Phi = inp_Phi;
}

double NavigationAlgorithm::get_Lambda()
{
    return Lambda;
}

double NavigationAlgorithm::get_Phi()
{
    return Phi;
}

double NavigationAlgorithm::get_diff_Lambda()
{
    return diff_Lambda;
}

double NavigationAlgorithm::get_diff_Phi()
{
    return diff_Phi;
}

void NavigationAlgorithm::input_accel_array(std::array<double, 3> accel)
{
    accel_array(0,0) = accel[0];
    accel_array(1,0) = accel[1];
    accel_array(2,0) = accel[2];
    calculate_nx_ny_nz();
}

void NavigationAlgorithm::input_C_Matrix(QGenericMatrix<3, 3, double> inp_C_Matrix)
{
    С_Matrix = inp_C_Matrix;
    emit signalStartCalculate();
}

void NavigationAlgorithm::calculate_coordinates()
{
    calculate_longitude();
    calculate_latitude();
    emit signalCoordinatesReady();
}

void NavigationAlgorithm::calculate_nx_ny_nz()
{
    ng_array = С_Matrix * accel_array;
    Vy = Vy + 0.005*(ng_array(1,0) - calculate_generationblock_ay());
}

double NavigationAlgorithm::calculate_generationblock_ax()
{
    return qPow(Vz, 2)/radius_Earth*qTan(Phi)+Vx*Vy/radius_Earth*qTan(Phi)+2*0.00007268518*Vz*qSin(Phi);
}

double NavigationAlgorithm::calculate_generationblock_ay()
{
    return -(qPow(Vz, 2)/radius_Earth) - qPow(Vx, 2)/radius_Earth - 2*0.00007268518*Vz*qCos(Phi)+9.81;
}

double NavigationAlgorithm::calculate_generationblock_az()
{
    return Vz*Vy/radius_Earth - Vx*Vz/radius_Earth*qTan(Phi) + 2*(Vy*0.00007268518*qCos(Phi)-0.00007268518*Vx*qSin(Phi));
}

void NavigationAlgorithm::calculate_longitude()
{
    Vz = Vz + 0.005*(ng_array(2,0) - calculate_generationblock_az());
    diff_Lambda = Vz * (1 / (radius_Earth * qCos(Phi)));
    emit signaldiff_LambdaReady(diff_Lambda);
    Lambda = Lambda + 0.005*diff_Lambda;
    emit signalLambdaReady(Lambda);
    emit signalLambdaDegreesReady(qRadiansToDegrees(Lambda));
}

void NavigationAlgorithm::calculate_latitude()
{
    Vx = Vx + 0.005*(ng_array(0,0) - calculate_generationblock_ax());
    diff_Phi = Vx * (1 / radius_Earth);
    emit signaldiff_PhiReady(diff_Phi);
    Phi = Phi + 0.005*diff_Phi;
    emit signalPhiReady(Phi);
    emit signalPhiDegreesReady(qRadiansToDegrees(Phi));
}



