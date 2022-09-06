#include "qserialio.h"

#include <QMessageBox>

QSerialIO::QSerialIO(QObject *parent) :
    QObject(parent)
{

}

QSerialIO::QSerialIO(QString portName_read, QString portName_write, qint32 baud, QSerialPort::DataBits bits, QSerialPort::StopBits sbits, QSerialPort::Parity parity, QSerialPort::FlowControl flow, QObject *parent):
    QObject(parent)
{
    serialPort_read.setPortName(portName_read);
    serialPort_read.setBaudRate(baud);
    serialPort_read.setDataBits(bits);
    serialPort_read.setStopBits(sbits);
    serialPort_read.setParity(parity);
    serialPort_read.setFlowControl(flow);
    serialPort_write.setPortName(portName_write);
    serialPort_write.setBaudRate(baud);
    serialPort_write.setDataBits(bits);
    serialPort_write.setStopBits(sbits);
    serialPort_write.setParity(parity);
    serialPort_write.setFlowControl(flow);
}

void QSerialIO::input_settings(QString portName_read, QString portName_write, qint32 baud, QSerialPort::DataBits bits, QSerialPort::StopBits sbits, QSerialPort::Parity parity, QSerialPort::FlowControl flow)
{
    serialPort_read.setPortName(portName_read);
    serialPort_read.setBaudRate(baud);
    serialPort_read.setDataBits(bits);
    serialPort_read.setStopBits(sbits);
    serialPort_read.setParity(parity);
    serialPort_read.setFlowControl(flow);
    serialPort_write.setPortName(portName_write);
    serialPort_write.setBaudRate(baud);
    serialPort_write.setDataBits(bits);
    serialPort_write.setStopBits(sbits);
    serialPort_write.setParity(parity);
    serialPort_write.setFlowControl(flow);
}

void QSerialIO::connect_ports()
{
    bool result = serialPort_read.open(QIODevice::ReadWrite);
    if (serialPort_read.portName() != serialPort_write.portName())
    {
        result = serialPort_write.open(QIODevice::ReadWrite);
    }
    if (!result)
    {
        QMessageBox msgBox;
        msgBox.setText("Порт не подключен");
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Порт подключен");
        msgBox.exec();
    }
    connect(&serialPort_read, SIGNAL(readyRead()), this, SLOT(handleRead()));
    connect(&serialPort_read, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
    connect(this, SIGNAL(signalDataRecieved()), this, SLOT(checkData()));
    connect(&serialPort_write, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
    connect(this, SIGNAL(signalWriteBegin()), this, SLOT(writeToDevice()));
    writeToDevice();
}

void QSerialIO::disconnect_ports()
{
    if (serialPort_read.isOpen())
        serialPort_read.close();
    if (serialPort_write.isOpen())
        serialPort_write.close();
}

void QSerialIO::handleRead()
{
    while (serialPort_read.waitForReadyRead(/*TIMEOUT*/ 5))
    {
        data_array +=serialPort_read.readAll();
    }
    emit signalDataRecieved();
}

void QSerialIO::handleError(QSerialPort::SerialPortError serialPortError)
{
//    QMessageBox msgBox;
//    msgBox.setText("Ошибка ввода/вывода");
//    if (serialPortError == QSerialPort::ReadError)
//    {
//        msgBox.exec();
//    }

}

void QSerialIO::writeToDevice()
{
    if (!serialPort_write.isOpen())
    {
        serialPort_read.write("9", 1);
        serialPort_read.waitForBytesWritten();
    }
    else
    {
        serialPort_write.write("9", 1);
        serialPort_write.waitForBytesWritten();
    }
}

void QSerialIO::checkData()
{
    if(!data_array.isEmpty())
    {
        data_string = data_array;
        if (data_string.contains("\r\n"))
        {
            data_array.clear();
            emit signalStringReady();
            emit signalWriteBegin();
        }
    }
}

QString QSerialIO::getDatastring()
{
    return data_string;
}

QSerialIO::~QSerialIO()
{
    if (serialPort_read.isOpen())
        serialPort_read.close();
    if (serialPort_write.isOpen())
        serialPort_write.close();
    emit finished_Port();
}
