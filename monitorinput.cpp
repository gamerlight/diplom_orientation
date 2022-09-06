#include "monitorinput.h"
#include "ui_monitorinput.h"

#include <QFileDialog>

MonitorInput::MonitorInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MonitorInput)
{
    ui->setupUi(this);
    ptr_serialReader = nullptr;
    monitor_init = 0;
}

MonitorInput::~MonitorInput()
{
    delete ui;
}

void MonitorInput::on_pushButton_clicked()
{
   this->accept();
}

void MonitorInput::inputPtr(QSerialIO *ptrr_serialReader)
{
    ptr_serialReader = ptrr_serialReader;
}

void MonitorInput::inputPtr(QFileIO *ptrr_fileReader)
{
    ptr_fileReader = ptrr_fileReader;
}

void MonitorInput::input_TextEdit()
{
    QString data;
    if(ptr_serialReader != nullptr)
    {
        data = ptr_serialReader->getDatastring();
        data.remove(data.lastIndexOf("\r\n"), 2);
    }
    if(ptr_fileReader != nullptr)
    {
       data = ptr_fileReader->getDatastring();
       data.remove(data.lastIndexOf("\n"), 1);
    }
    ui->textEdit->append(data);
}

void MonitorInput::on_pushButton_2_clicked()
{
    if (monitor_init == 0)
    {
        monitor_init = 1;
        connect(ptr_serialReader, SIGNAL(signalStringReady()), this, SLOT(input_TextEdit()));
        connect(ptr_fileReader, SIGNAL(signalStringReady()), this, SLOT(input_TextEdit()));
    }
    else
    {
        monitor_init = 0;
        disconnect(ptr_serialReader, SIGNAL(signalStringReady()), this, SLOT(input_TextEdit()));
        disconnect(ptr_fileReader, SIGNAL(signalStringReady()), this, SLOT(input_TextEdit()));
    }
}


void MonitorInput::on_pushButton_3_clicked()
{
    ui->textEdit->clear();
}


void MonitorInput::on_pushButton_4_clicked()
{
    QString fileWriter;
    fileWriter = QFileDialog::getSaveFileName(0, "Открыть", "", "*.txt");
    QFile file(fileWriter);
    file.open(QIODevice::WriteOnly);
    file.write(ui->textEdit->toPlainText().toUtf8());
    file.close();
}

