#include "parallelprocessthread.h"

ParallelProcessThread::ParallelProcessThread(QObject *parent)
    : QObject{parent}
{

}

ParallelProcessThread::~ParallelProcessThread()
{
    disconnect(ParallelThread_1, SIGNAL(started()), Block1, SLOT(calculate_C_Matrix()));
    disconnect(ParallelThread_2, SIGNAL(started()), Block2, SLOT(calculate_coordinates()));
    disconnect(ParallelThread_3, SIGNAL(started()), Block3, SLOT(calculate_OmegaGMatrix()));
    disconnect(strToFloat, SIGNAL(signalGyroReady(std::array<double, 3>)), Block1, SLOT(input_OmegaMatrix(std::array<double, 3>)));
    disconnect(strToFloat, SIGNAL(signalAccelReady(std::array<double, 3>)), Block2, SLOT(input_accel_array(std::array<double, 3>)));
    disconnect(Block1, SIGNAL(signalC_MatrixReady(QGenericMatrix <3,3,double>)), Block2, SLOT(input_C_Matrix(QGenericMatrix <3,3,double>)));
    disconnect(Block2, SIGNAL(signalPhiReady(double)), Block3, SLOT(input_Phi(double)));
    disconnect(Block2, SIGNAL(signaldiff_LambdaReady(double)), Block3, SLOT(input_diff_Lambda(double)));
    disconnect(Block2, SIGNAL(signaldiff_PhiReady(double)), Block3, SLOT(input_diff_Phi(double)));
    disconnect(Block3, SIGNAL(signalOmegaGMatrix(QGenericMatrix <3,3,double>)), Block1, SLOT(input_OmegaGMatrix(QGenericMatrix <3,3,double>)));
    disconnect(Block1, SIGNAL(signalStartCMatrix()), Block1, SLOT(calculate_C_Matrix()));
    disconnect(Block2, SIGNAL(signalStartCalculate()), Block2, SLOT(calculate_coordinates()));
    disconnect(Block3, SIGNAL(signalStartCalculate()), Block3, SLOT(calculate_OmegaGMatrix()));
    delete ParallelThread_1;
    delete ParallelThread_2;
    delete ParallelThread_3;
    emit finished_thread();
}

void ParallelProcessThread::init_Blocks()
{
    ParallelThread_1 = new QThread();
    ParallelThread_2 = new QThread();
    ParallelThread_3 = new QThread();
    Block1->moveToThread(ParallelThread_1);
    Block2->moveToThread(ParallelThread_2);
    Block3->moveToThread(ParallelThread_3);
    connect(strToFloat, SIGNAL(signalGyroReady(std::array<double, 3>)), Block1, SLOT(input_OmegaMatrix(std::array<double, 3>)));
    connect(strToFloat, SIGNAL(signalAccelReady(std::array<double, 3>)), Block2, SLOT(input_accel_array(std::array<double, 3>)));
    connect(Block1, SIGNAL(signalC_MatrixReady(QGenericMatrix <3,3,double>)), Block2, SLOT(input_C_Matrix(QGenericMatrix <3,3,double>)));
    connect(Block2, SIGNAL(signalPhiReady(double)), Block3, SLOT(input_Phi(double)));
    connect(Block2, SIGNAL(signaldiff_LambdaReady(double)), Block3, SLOT(input_diff_Lambda(double)));
    connect(Block2, SIGNAL(signaldiff_PhiReady(double)), Block3, SLOT(input_diff_Phi(double)));
    connect(Block3, SIGNAL(signalOmegaGMatrix(QGenericMatrix <3,3,double>)), Block1, SLOT(input_OmegaGMatrix(QGenericMatrix <3,3,double>)));
    connect(Block3, SIGNAL(signalOmegaGMatrix(QGenericMatrix <3,3,double>)), this, SLOT(timer_stop(QGenericMatrix <3,3,double>)));
    connect(Block1, SIGNAL(signalStartCMatrix()), Block1, SLOT(calculate_C_Matrix()));
    connect(Block1, SIGNAL(signalStartCMatrix()), this, SLOT(timer_start()));
    connect(Block2, SIGNAL(signalStartCalculate()), Block2, SLOT(calculate_coordinates()));
    connect(Block3, SIGNAL(signalStartCalculate()), Block3, SLOT(calculate_OmegaGMatrix()));
    connect(ParallelThread_1, SIGNAL(started()), Block1, SLOT(calculate_C_Matrix()));
    connect(ParallelThread_2, SIGNAL(started()), Block2, SLOT(calculate_coordinates()));
    connect(ParallelThread_3, SIGNAL(started()), Block3, SLOT(calculate_OmegaGMatrix()));
    ParallelThread_1->start();
    ParallelThread_2->start();
    ParallelThread_3->start();
}

void ParallelProcessThread::input_Blocks(OrientationAlgorithm *Blo1, NavigationAlgorithm *Blo2, GeoAngularVelocityVector *Blo3, StringToFloatMeasurements *stf)
{
    Block1 = Blo1;
    Block2 = Blo2;
    Block3 = Blo3;
    strToFloat = stf;
}

void ParallelProcessThread::timer_start()
{
    timer.start();
}

void ParallelProcessThread::timer_stop(QGenericMatrix<3, 3, double>)
{
    int time_timer = timer.nsecsElapsed();
    emit signalTime(time_timer);
    emit signalDataInput();
}
