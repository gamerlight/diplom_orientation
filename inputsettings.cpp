#include "inputsettings.h"
#include "ui_inputsettings.h"

#include <QtSerialPort/QSerialPortInfo>
#include <QFileDialog>

inputsettings::inputsettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inputsettings)
{
    ui->setupUi(this);
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

void inputsettings::on_pushButton_clicked()
{
    portNamestr = ui->comboBox_2->currentText();
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

