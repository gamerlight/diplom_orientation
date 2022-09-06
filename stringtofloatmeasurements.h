#ifndef STRINGTOFLOATMEASUREMENTS_H
#define STRINGTOFLOATMEASUREMENTS_H

#include <QObject>
#include <QString>

#include <array>

#include <qserialio.h>
#include <qfileio.h>

class StringToFloatMeasurements : public QObject
{
    Q_OBJECT
public:
    StringToFloatMeasurements(QSerialIO *ptrr_serialReader);
    StringToFloatMeasurements(QFileIO *ptrr_fileReader);
    std::array<double, 3> getAccel();
    std::array<double, 3> getGyro();

signals:
    void signalArrayReady();
    void signalAccelReady(std::array<double, 3> sig_accel);
    void signalGyroReady(std::array<double, 3> sig_gyro);

private slots:
    void putString();

private:
    void convertStringtoFloats();
    QString string_data;
    std::array<double, 3> accel;
    std::array<double, 3> gyro;
    QSerialIO *ptr_serialReader = nullptr;
    QFileIO *ptr_fileReader = nullptr;
};

#endif // STRINGTOFLOATMEASUREMENTS_H
