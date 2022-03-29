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
        if (input_settings.getInputMethod() == 0)
        {
            serialManager = new SerialPortManager(input_settings.getPortNamestr());
            serialReader = new QSerialIO(serialManager->getSerialPort());
            strToFloat = new StringToFloatMeasurements(serialReader);
            monitor_input.inputPtr(serialReader);
            plot_monitor.input_ptrStF(strToFloat);
        }
        else
        {
            if (serialReader != nullptr)
            {
                delete serialReader;
                delete serialManager;
                delete strToFloat;
            }
            //TODO Добавить создание потока для файла
        }
    }
}


void MainWindow::on_action_3_triggered()
{
    monitor_input.show();
}


void MainWindow::on_action_2_triggered()
{
    plot_monitor.show();
}

