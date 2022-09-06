#ifndef NAVIGATIONALGORITHMPARALLEL_H
#define NAVIGATIONALGORITHMPARALLEL_H

#include "navigationalgorithm.h"

#include <omp.h>

class NavigationAlgorithmParallel : public NavigationAlgorithm
{
    Q_OBJECT
public:
    NavigationAlgorithmParallel();

    // NavigationAlgorithm interface
protected:
    virtual void calculate_nx_ny_nz() override;

    // NavigationAlgorithm interface
public slots:
    virtual void calculate_coordinates() override;
};

#endif // NAVIGATIONALGORITHMPARALLEL_H
