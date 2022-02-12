#include "inputsettings.h"
#include "ui_inputsettings.h"

#include <QtSerialPort/QSerialPortInfo>

inputsettings::inputsettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inputsettings)
{
    ui->setupUi(this);
}

inputsettings::~inputsettings()
{
    delete ui;
}

void inputsettings::on_pushButton_clicked()
{
    this->accept();
}

