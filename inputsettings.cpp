#include "inputsettings.h"
#include "ui_inputsettings.h"

#include <QtSerialPort/QSerialPortInfo>
#include <QFileDialog>

inputsettings::inputsettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inputsettings)
{
    ui->setupUi(this);
    inputMethod = 0;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->comboBox_2->addItem(info.portName());
        ui->comboBox_3->addItem(info.portName());
    }
}

inputsettings::~inputsettings()
{
    delete ui;
}

QString inputsettings::getPortNamestr_read()
{
    return portNamestr_read;
}

QString inputsettings::getPortNamestr_write()
{
    return portNamestr_write;
}

QString inputsettings::getFileReader()
{
    return fileReader;
}

bool inputsettings::getInputMethod()
{
    return inputMethod;
}

void inputsettings::on_pushButton_clicked()
{
    portNamestr_read = ui->comboBox_2->currentText();
    portNamestr_write = ui->comboBox_3->currentText();
    this->accept();
}


void inputsettings::on_comboBox_currentIndexChanged(int index)
{
    if (ui->comboBox->currentIndex() == 0)
    {
        ui->comboBox_2->setEnabled(true);
        ui->comboBox_3->setEnabled(true);
        ui->pushButton_2->setEnabled(false);
        inputMethod = 0;
    }
    else
    {
        ui->comboBox_2->setEnabled(false);
        ui->comboBox_3->setEnabled(false);
        ui->pushButton_2->setEnabled(true);
        inputMethod = 1;
    }
}


void inputsettings::on_pushButton_2_clicked()
{
    fileReader = QFileDialog::getOpenFileName(0, "Открыть", "", "*.txt *.csv");
}

