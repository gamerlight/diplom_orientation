#include "qserialio.h"

#include <QMessageBox>

QSerialIO::QSerialIO(QSerialPort *serialPort, QObject *parent) :
    QObject(parent)
{
    this->serialPort = serialPort;
    connect(serialPort, SIGNAL(readyRead()), this, SLOT(handleRead()));
    connect(serialPort, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
}

void QSerialIO::handleRead()
{
    while (serialPort->waitForReadyRead(50))
    {
        data_array += serialPort->readLine();
    }
    if (!data_array.isEmpty())
    {
        data_string = data_array;
        emit signalStringReady();
    }
    data_array.clear();
}

void QSerialIO::handleError(QSerialPort::SerialPortError serialPortError)
{
    QMessageBox msgBox;
    msgBox.setText("Ошибка ввода/вывода");
    //msgBox.exec();
}

QString QSerialIO::get_datastring()
{
    return data_string;
}
