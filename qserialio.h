#ifndef QSERIALIO_H
#define QSERIALIO_H

#include <QtSerialPort/QSerialPort>
#include <QString>

class QSerialIO : public QObject
{
    Q_OBJECT
public:
    explicit QSerialIO(QSerialPort *serialPort, QObject *parent = nullptr);
    QString getDatastring();

signals:
    void signalStringReady();

public slots:
    void handleRead();
    void handleError(QSerialPort::SerialPortError serialPortError);

private:
    QString data_string;
    QByteArray data_array;
    QSerialPort *serialPort = nullptr;
};

#endif // QSERIALIO_H
