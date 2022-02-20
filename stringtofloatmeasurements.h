#ifndef STRINGTOFLOATMEASUREMENTS_H
#define STRINGTOFLOATMEASUREMENTS_H

#include <QObject>
#include <QString>

#include <array>

class StringToFloatMeasurements : public QObject
{
    Q_OBJECT
public:
    StringToFloatMeasurements();
    void putString(QString input_string);
    void convertStringtoFloats();

private:
    QString string_data;
    std::array<float, 6> accel_gyro;
};

#endif // STRINGTOFLOATMEASUREMENTS_H
