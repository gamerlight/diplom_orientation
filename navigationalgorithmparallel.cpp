#include "navigationalgorithmparallel.h"

NavigationAlgorithmParallel::NavigationAlgorithmParallel()
{

}


void NavigationAlgorithmParallel::calculate_nx_ny_nz()
{
    QGenericMatrix <1,3,double> ng_array_n;
    ng_array_n.fill(0);
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < 3; i++)
      {
          for (int k = 0; k < 3; k++)
            ng_array_n(i,0) += С_Matrix(i,k) * accel_array(k,0);
      }
    ng_array = ng_array_n;
    Vy = Vy + 0.005*(ng_array(1,0) - calculate_generationblock_ay());
}


void NavigationAlgorithmParallel::calculate_coordinates()
{
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            calculate_latitude();
        }
        #pragma omp section
        {
            calculate_longitude();
        }
    }
    emit signalCoordinatesReady();
}
