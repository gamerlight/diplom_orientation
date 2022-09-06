#ifndef SERIALPROCESSTHREAD_H
#define SERIALPROCESSTHREAD_H

#include <QObject>

#include "orientationalgorithm.h"
#include "navigationalgorithm.h"
#include "geoangularvelocityvector.h"
#include "stringtofloatmeasurements.h"

class SerialProcessThread : public QObject
{
    Q_OBJECT
public:
    explicit SerialProcessThread(QObject *parent = nullptr);
    ~SerialProcessThread();
public slots:
    void input_Blocks(OrientationAlgorithm*, NavigationAlgorithm *, GeoAngularVelocityVector *, StringToFloatMeasurements *);
    void serial_process();

signals:
    void signalDataInput();
    void finished_process();
    void signalTime(int);

private:
    OrientationAlgorithm *Block1;
    NavigationAlgorithm *Block2;
    GeoAngularVelocityVector *Block3;
    StringToFloatMeasurements *strToFloat;
};

#endif // SERIALPROCESSTHREAD_H
