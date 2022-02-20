#include "stringtofloatmeasurements.h"

StringToFloatMeasurements::StringToFloatMeasurements()
{

}

void StringToFloatMeasurements::putString(QString input_string)
{
    string_data = input_string;
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
