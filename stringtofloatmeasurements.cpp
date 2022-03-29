#include "stringtofloatmeasurements.h"

StringToFloatMeasurements::StringToFloatMeasurements(QSerialIO *ptrr_serialReader)
{
    ptr_serialReader = ptrr_serialReader;
    connect(ptr_serialReader, SIGNAL(signalStringReady()), this, SLOT(putString()));
}

std::array<float, 3> StringToFloatMeasurements::getAccel()
{
    return accel;
}

std::array<float, 3> StringToFloatMeasurements::getGyro()
{
    return gyro;
}

void StringToFloatMeasurements::putString()
{
    string_data = ptr_serialReader->getDatastring();
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
            accel[i] = buf.toFloat();
        }
        else
        {
            gyro[j] = buf.toFloat();
            j++;
        }
    }
    emit signalArrayReady();
}
