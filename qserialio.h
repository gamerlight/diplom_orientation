#ifndef QSERIALIO_H
#define QSERIALIO_H

#include <QObject>
#include <QString>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class QSerialIO : public QObject
{
    Q_OBJECT
public:
    QSerialPort serialPort_read;
    QSerialPort serialPort_write;
    explicit QSerialIO(QObject *parent = nullptr);
    QSerialIO(QString portName_read, QString portName_write,
                      qint32 baud = QSerialPort::Baud9600,
                      QSerialPort::DataBits bits = QSerialPort::Data8,
                      QSerialPort::StopBits sbits = QSerialPort::OneStop,
                      QSerialPort::Parity parity = QSerialPort::NoParity,
                      QSerialPort::FlowControl flow = QSerialPort::NoFlowControl, QObject *parent = nullptr);
    void input_settings(QString portName_read, QString portName_write,
                        qint32 baud = QSerialPort::Baud9600,
                        QSerialPort::DataBits bits = QSerialPort::Data8,
                        QSerialPort::StopBits sbits = QSerialPort::OneStop,
                        QSerialPort::Parity parity = QSerialPort::NoParity,
                        QSerialPort::FlowControl flow = QSerialPort::NoFlowControl);
    QString getDatastring();
    ~QSerialIO();

signals:
    void signalStringReady();
    void signalWriteBegin();
    void signalDataRecieved();
    void finished_Port();

public slots:
    void handleRead();
    void handleError(QSerialPort::SerialPortError serialPortError);
    void writeToDevice();
    void checkData();
    void connect_ports();
    void disconnect_ports();
private:
    QString data_string;
    QByteArray data_array;

};

#endif // QSERIALIO_H
