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
    std::array<float, 6> getAccel_gyro();

signals:
    void signalArrayReady();

private slots:
    void putString();

private:
    void convertStringtoFloats();
    QString string_data;
    std::array<float, 6> accel_gyro;
    QSerialIO *ptr_serialReader = nullptr;
};

#endif // STRINGTOFLOATMEASUREMENTS_H
