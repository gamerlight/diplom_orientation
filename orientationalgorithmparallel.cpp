#include "orientationalgorithmparallel.h"

OrientationAlgorithmParallel::OrientationAlgorithmParallel()
{
    #pragma omp parallel for collapse(2)
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


void OrientationAlgorithmParallel::calculate_C_Matrix()
{
    QGenericMatrix<3, 3, double> A;
    QGenericMatrix<3, 3, double> B;
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            A = multiplyMatrix(Сc_Matrix, OmegaMatrix);
        }
        #pragma omp section
        {
            B = multiplyMatrix(OmegaGMatrix, Сc_Matrix);
        }
    }
    QGenericMatrix<3, 3, double> diff_Matrix;
    diff_Matrix = subtractMatrix(A, B);
    diff_Matrix = multiplyMatrix(0.005, diff_Matrix);
    Сc_Matrix = addMatrix(Сc_Matrix, diff_Matrix);
    emit signalC_MatrixReady(Сc_Matrix);
}

QGenericMatrix<3, 3, double> OrientationAlgorithmParallel::multiplyMatrix(QGenericMatrix<3, 3, double> A, QGenericMatrix<3, 3, double> B)
{
    QGenericMatrix<3, 3, double> R;
    R.fill(0);
    #pragma omp parallel for
    for (int i = 0; i < 3; i++)
      {
        for (int j = 0; j < 3; j++)
        {
          for (int k = 0; k < 3; k++)
            R(i,j) += A(i,k) * B(k,j);
        }
      }
    return R;
}

QGenericMatrix<3, 3, double> OrientationAlgorithmParallel::multiplyMatrix(double A, QGenericMatrix<3, 3, double> B)
{
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            B(i,j)= B(i,j)*A;
        }
    return B;
}

QGenericMatrix<3, 3, double> OrientationAlgorithmParallel::addMatrix(QGenericMatrix<3, 3, double> A, QGenericMatrix<3, 3, double> B)
{
    QGenericMatrix<3, 3, double> R;
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            R(i,j)= A(i,j)+B(i,j);
        }
    return R;
}

QGenericMatrix<3, 3, double> OrientationAlgorithmParallel::subtractMatrix(QGenericMatrix<3, 3, double> A, QGenericMatrix<3, 3, double> B)
{
    QGenericMatrix<3, 3, double> R;
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            R(i,j)= A(i,j)-B(i,j);
        }
    return R;
}
