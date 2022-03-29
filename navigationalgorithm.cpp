#include "navigationalgorithm.h"

NavigationAlgorithm::NavigationAlgorithm()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            if (i != j)
                С_Matrix(i, j) = 0;
            else
                С_Matrix(i, j) = 1;
        }
}

void NavigationAlgorithm::input_ptrStF(StringToFloatMeasurements *ptr)
{
    ptr_StringtoFloat = ptr;
}

void NavigationAlgorithm::input_OmegaMatrix()
{
    std::array<float, 3> gyro;
    gyro = ptr_StringtoFloat->getGyro();
    OmegaMatrix(0, 0) = 0;
    OmegaMatrix(1, 1) = 0;
    OmegaMatrix(2, 2) = 0;
    OmegaMatrix(2, 0) = OmegaMatrix(0, 2) = gyro[1];
    OmegaMatrix(1, 0) = gyro[2];
    OmegaMatrix(0, 1) = -gyro[2];
    OmegaMatrix(2, 1) = gyro[0];
    OmegaMatrix(1, 2) = -gyro[2];
}

void NavigationAlgorithm::input_OmegaGMatrix()
{

}

