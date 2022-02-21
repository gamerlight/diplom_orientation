#include "stringtofloatmeasurements.h"

StringToFloatMeasurements::StringToFloatMeasurements(QSerialIO *ptrr_serialReader)
{
    ptr_serialReader = ptrr_serialReader;
    connect(ptr_serialReader, SIGNAL(signalStringReady()), this, SLOT(putString()));
}

void StringToFloatMeasurements::putString()
{
    string_data = ptr_serialReader->getDatastring();
}


void StringToFloatMeasurements::convertStringtoFloats()
{
    for (int i = 0; i < 6; i++)
    {
        QString buf;
        int j;
        while (string_data[0] != '\t')
        {
            buf += string_data[0];
            string_data.remove(0, 1);
        }
        string_data.remove(0, 1);
        accel_gyro[i] = buf.toFloat();
    }
}
