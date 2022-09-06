#include "stringtofloatmeasurements.h"

StringToFloatMeasurements::StringToFloatMeasurements(QSerialIO *ptrr_serialReader)
{
    ptr_serialReader = ptrr_serialReader;
    connect(ptr_serialReader, SIGNAL(signalStringReady()), this, SLOT(putString()));
}

StringToFloatMeasurements::StringToFloatMeasurements(QFileIO *ptrr_fileReader)
{
    ptr_fileReader = ptrr_fileReader;
    connect(ptr_fileReader, SIGNAL(signalStringReady()), this, SLOT(putString()));
}

std::array<double, 3> StringToFloatMeasurements::getAccel()
{
    return accel;
}

std::array<double, 3> StringToFloatMeasurements::getGyro()
{
    return gyro;
}

void StringToFloatMeasurements::putString()
{
    if (ptr_serialReader != nullptr)
        string_data = ptr_serialReader->getDatastring();
    if (ptr_fileReader != nullptr)
        string_data = ptr_fileReader->getDatastring();
    convertStringtoFloats();
}

void StringToFloatMeasurements::convertStringtoFloats()
{
    int j = 0;
    for (int i = 0; i < 6; i++)
    {
        QString buf;
        while (string_data[0] != '\t')
        {
            buf += string_data[0];
            string_data.remove(0, 1);
        }
        string_data.remove(0, 1);
        if (i < 3)
        {
            accel[i] = buf.toDouble();
            if ((accel[j] < 0.05)&&(accel[j] > -0.05))
                accel[j] = 0;
        }
        else
        {
            gyro[j] = buf.toDouble();
            if ((gyro[j] < 0.05)&&(gyro[j] > -0.05))
                gyro[j] = 0;
            j++;
        }
    }
    emit signalArrayReady();
    emit signalAccelReady(accel);
    emit signalGyroReady(gyro);
}
