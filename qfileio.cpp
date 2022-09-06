#include "qfileio.h"

QFileIO::QFileIO(QObject *parent)
    : QObject{parent}
{

}

QFileIO::QFileIO(QString fileP, QObject *parent) :
    QObject(parent)
{
    this->filePath = fileP;
    file.setFileName(filePath);
}

void QFileIO::input_filePath(QString fileP)
{
    this->filePath = fileP;
    file.setFileName(filePath);
}

QString QFileIO::getDatastring()
{
    return data_string;
}

QFileIO::~QFileIO()
{
    file.close();
    emit finished_File();
}

void QFileIO::start_read()
{
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    read_string();
}

void QFileIO::read_string()
{
    if (!file.atEnd())
    {
        data_string.clear();
        data_string = file.readLine();
        emit signalStringReady();
    }
}
