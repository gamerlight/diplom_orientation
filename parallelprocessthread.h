#ifndef PARALLELPROCESSTHREAD_H
#define PARALLELPROCESSTHREAD_H

#include "geoangularvelocityvector.h"
#include "navigationalgorithm.h"
#include "orientationalgorithm.h"

#include <QObject>
#include <QThread>

class ParallelProcessThread : public QObject
{
    Q_OBJECT
public:
    explicit ParallelProcessThread(QObject *parent = nullptr);
    ~ParallelProcessThread();

public slots:
    void init_Blocks();
    void input_Blocks(OrientationAlgorithm*, NavigationAlgorithm *, GeoAngularVelocityVector *, StringToFloatMeasurements *);


signals:
    void finished_thread();
    void signalDataInput();
    void signalTime(int);

private slots:
    void timer_start();
    void timer_stop(QGenericMatrix <3,3,double>);

private:
    OrientationAlgorithm *Block1;
    NavigationAlgorithm *Block2;
    GeoAngularVelocityVector *Block3;
    StringToFloatMeasurements *strToFloat;

    QThread *ParallelThread_1;
    QThread *ParallelThread_2;
    QThread *ParallelThread_3;

    QElapsedTimer timer;

};

#endif // PARALLELPROCESSTHREAD_H
