#include "serialprocessthread.h"

#include <QThread>

SerialProcessThread::SerialProcessThread(QObject *parent)
    : QObject{parent}
{

}

void SerialProcessThread::input_Blocks(OrientationAlgorithm *Blo1, NavigationAlgorithm *Blo2, GeoAngularVelocityVector *Blo3, StringToFloatMeasurements *stf)
{
    Block1 = Blo1;
    Block2 = Blo2;
    Block3 = Blo3;
    strToFloat = stf;
}

void SerialProcessThread::serial_process()
{
    QElapsedTimer timer;
    timer.start();
    Block2->input_accel_array(strToFloat->getAccel());
    Block1->input_OmegaGMatrix(Block3->get_OmegaGMatrix());
    Block1->input_OmegaMatrix(strToFloat->getGyro());
    Block1->calculate_C_Matrix();
    Block1->calucaltePsiThetaGamma();
    Block2->input_C_Matrix(Block1->getC_Matrix());
    Block2->calculate_coordinates();
    Block3->input_Phi(Block2->get_Phi());
    Block3->input_diff_Lambda(Block2->get_diff_Lambda());
    Block3->input_diff_Phi(Block2->get_diff_Phi());
    Block3->calculate_OmegaGMatrix();
    int time_timer = timer.nsecsElapsed();
    emit signalTime(time_timer);
    emit signalDataInput();
}

SerialProcessThread::~SerialProcessThread()
{
    emit finished_process();
}
