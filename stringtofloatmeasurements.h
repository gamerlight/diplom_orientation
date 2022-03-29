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
    std::array<float, 3> getAccel();
    std::array<float, 3> getGyro();

signals:
    void signalArrayReady();

private slots:
    void putString();

private:
    void convertStringtoFloats();
    QString string_data;
    std::array<float, 3> accel;
    std::array<float, 3> gyro;
    QSerialIO *ptr_serialReader = nullptr;
};

#endif // STRINGTOFLOATMEASUREMENTS_H
