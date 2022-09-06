#include "serialportmanager.h"
#include <QMessageBox>

SerialPortManager::SerialPortManager()
{

}

SerialPortManager::SerialPortManager(QString portName,
                                     qint32 baud,
                                     QSerialPort::DataBits bits,
                                     QSerialPort::StopBits sbits,
                                     QSerialPort::Parity parity,
                                     QSerialPort::FlowControl flow)
{
    this->serialPort = new QSerialPort();
    this->portName = portName;
    this->serialPort->setPortName(portName);
    this->serialPort->setBaudRate(baud);
    this->serialPort->setDataBits(bits);
    this->serialPort->setStopBits(sbits);
    this->serialPort->setParity(parity);
    this->serialPort->setFlowControl(flow);

    bool result = this->serialPort->open(QIODevice::ReadWrite);

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
}

SerialPortManager::~SerialPortManager()
{
    this->serialPort->close();
}

QSerialPort *SerialPortManager::getSerialPort() const
{
    return this->serialPort;
}
