#include "monitorinput.h"
#include "ui_monitorinput.h"

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

void MonitorInput::input_TextEdit()
{
    QString data = ptr_serialReader->getDatastring();
    data.remove(data.lastIndexOf("\r\n"), 2);
    ui->textEdit->append(data);
}

void MonitorInput::on_pushButton_2_clicked()
{
    if (monitor_init == 0)
    {
        monitor_init = 1;
        connect(ptr_serialReader, SIGNAL(signalStringReady()), this, SLOT(input_TextEdit()));
    }
    else
    {
        monitor_init = 0;
        disconnect(ptr_serialReader, SIGNAL(signalStringReady()), 0, 0);
    }
}


void MonitorInput::on_pushButton_3_clicked()
{
    ui->textEdit->clear();
}

