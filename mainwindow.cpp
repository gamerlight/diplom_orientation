#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
    if (input_settings.exec() == QDialog::Accepted)
    {
        if (input_settings.inputMethod == 0)
        {
            serialManager = new SerialPortManager(input_settings.portNamestr);
            serialReader = new QSerialIO(serialManager->getSerialPort());
            monitor_input.inputPtr(serialReader);
        }
        else
        {
            //TODO Добавить создание потока для файла
        }
    }
}


void MainWindow::on_action_3_triggered()
{
    monitor_input.show();
}

