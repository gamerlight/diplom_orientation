#include "orientationalgorithm.h"
#include <QtMath>

OrientationAlgorithm::OrientationAlgorithm()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            if (i != j)
                Сc_Matrix(i, j) = 0;
            else
                Сc_Matrix(i, j) = 1;
        }
    OmegaMatrix.fill(0);
}

void OrientationAlgorithm::input_ptrStF(StringToFloatMeasurements *ptr)
{
    ptr_StringtoFloat = ptr;
}

void OrientationAlgorithm::input_psi(double inp)
{
    if (inp < 180)
    {
        psi = qDegreesToRadians(-inp);
    }
    else
    {
        psi = qDegreesToRadians(360-inp);
    }
    correction_C_matrix();
}

QGenericMatrix<3, 3, double> OrientationAlgorithm::getC_Matrix()
{
    return Сc_Matrix;
}

void OrientationAlgorithm::block_process()
{
    calculate_C_Matrix();
    calucaltePsiThetaGamma();
}

void OrientationAlgorithm::correction_C_matrix()
{
    Сc_Matrix(0, 0) = qCos(theta)*qCos(psi);
    Сc_Matrix(0, 1) = -qCos(gamma)*qCos(psi)*qSin(theta)+qSin(gamma)*qSin(psi);
    Сc_Matrix(0, 2) = qSin(gamma)*qCos(psi)*qSin(theta)+qCos(gamma)*qSin(psi);
    Сc_Matrix(1, 0) = qSin(theta);
    Сc_Matrix(1, 1) = qCos(gamma)*qCos(theta);
    Сc_Matrix(1, 2) = -qSin(gamma)*qCos(theta);
    Сc_Matrix(2, 0) = -qCos(theta)*qSin(psi);
    Сc_Matrix(2, 1) = qCos(gamma)*qSin(psi)*qSin(theta)+qSin(gamma)*qCos(psi);
    Сc_Matrix(2, 2) = -qSin(gamma)*qSin(psi)*qSin(theta)+qCos(gamma)*qCos(psi);
}

void OrientationAlgorithm::input_OmegaMatrix()
{
    std::array<double, 3> gyro;
    gyro = ptr_StringtoFloat->getGyro();
    for (int i = 0; i < 3; i++)
    {
        gyro[i] = qDegreesToRadians(gyro[i]);
    }
    OmegaMatrix(0, 0) = 0;
    OmegaMatrix(0, 1) = -gyro[2];
    OmegaMatrix(0, 2) = gyro[1];
    OmegaMatrix(1, 0) = gyro[2];
    OmegaMatrix(1, 1) = 0;
    OmegaMatrix(1, 2) = -gyro[0];
    OmegaMatrix(2, 0) = -gyro[1];
    OmegaMatrix(2, 1) = gyro[0];
    OmegaMatrix(2, 2) = 0;
}

void OrientationAlgorithm::input_OmegaMatrix(std::array<double, 3> gyro)
{
    for (int i = 0; i < 3; i++)
    {
        gyro[i] = qDegreesToRadians(gyro[i]);
    }
    OmegaMatrix(0, 0) = 0;
    OmegaMatrix(0, 1) = -gyro[2];
    OmegaMatrix(0, 2) = gyro[1];
    OmegaMatrix(1, 0) = gyro[2];
    OmegaMatrix(1, 1) = 0;
    OmegaMatrix(1, 2) = -gyro[0];
    OmegaMatrix(2, 0) = -gyro[1];
    OmegaMatrix(2, 1) = gyro[0];
    OmegaMatrix(2, 2) = 0;
    emit signalStartCMatrix();
}

void OrientationAlgorithm::input_OmegaGMatrix(QGenericMatrix <3,3,double> inp_OmegaGmatrix)
{
    OmegaGMatrix = inp_OmegaGmatrix;
}

void OrientationAlgorithm::calculate_C_Matrix()
{
    Сc_Matrix = Сc_Matrix +  0.005*(Сc_Matrix*OmegaMatrix - OmegaGMatrix*Сc_Matrix);
    emit signalC_MatrixReady(Сc_Matrix);
}

void OrientationAlgorithm::calucaltePsiThetaGamma()
{
    psi = qAtan((-Сc_Matrix(2, 0))/Сc_Matrix(0, 0));
    theta = qAsin(Сc_Matrix(1,0));
    gamma = qAtan((-Сc_Matrix(1, 2))/Сc_Matrix(1, 1));
    std::array<double, 3> angles;
    angles [0] = psi; angles[1] = theta; angles[2] = gamma;
    emit signalAnglesReady(angles);
}
