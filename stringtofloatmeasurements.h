#ifndef STRINGTOFLOATMEASUREMENTS_H
#define STRINGTOFLOATMEASUREMENTS_H

#include <QObject>
#include <QString>

#include <array>

#include <qserialio.h>

class StringToFloatMeasurements : public QObject
{
    Q_OBJECT
public:
    StringToFloatMeasurements(QSerialIO *ptrr_serialReader);

private slots:
    void convertStringtoFloats();
    void putString();

private:
    QString string_data;
    std::array<float, 6> accel_gyro;
    QSerialIO *ptr_serialReader = nullptr;
};

#endif // STRINGTOFLOATMEASUREMENTS_H
