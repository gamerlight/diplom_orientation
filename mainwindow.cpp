#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QString>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    track = new QSplineSeries();
    chart = new Chart();
    chart->addSeries(track);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->hide();
    chart->createDefaultAxes();
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setChart(chart);
    serialReader = nullptr;
    fileReader = nullptr;
    serial_process = nullptr;
    parallel_process = nullptr;
    average_time_series = new QSplineSeries();
    ui->graphicsView_2->chart()->addSeries(average_time_series);
    ui->graphicsView_2->chart()->setAnimationOptions(QChart::SeriesAnimations);
    ui->graphicsView_2->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_2->chart()->legend()->hide();
    ui->graphicsView_2->chart()->createDefaultAxes();
    ui->graphicsView_2->chart()->axisX()->setRange(0, 15);
    ui->graphicsView_2->chart()->axisY()->setRange(-10, 1000000);
    aver_count = 0;
}

MainWindow::~MainWindow()
{
    delete chart;
    delete ui;
}

Ui::MainWindow *MainWindow::getMainWindow()
{
    return ui;
}

void MainWindow::on_action_triggered()
{
    if (input_settings.exec() == QDialog::Accepted)
    {
        if (input_settings.getInputMethod() == 0)
        {
            if (fileReader != nullptr)
            {
                IO_thread->quit();
                delete fileReader;
                delete IO_thread;
                delete strToFloat;
            }
            IO_thread = new QThread();
            if (input_settings.getPortNamestr_read() == input_settings.getPortNamestr_write())
            {
                serialReader = new QSerialIO(input_settings.getPortNamestr_read(), input_settings.getPortNamestr_read());
                serialReader->moveToThread(IO_thread);
                serialReader->serialPort_read.moveToThread(IO_thread);
            }
            else
            {
                serialReader = new QSerialIO(input_settings.getPortNamestr_read(), input_settings.getPortNamestr_write());
                serialReader->moveToThread(IO_thread);
                serialReader->serialPort_read.moveToThread(IO_thread);
                serialReader->serialPort_write.moveToThread(IO_thread);
            }
            strToFloat = new StringToFloatMeasurements(serialReader);
            strToFloat->moveToThread(IO_thread);
            monitor_input.inputPtr(serialReader);
            connect(IO_thread, SIGNAL(started()), serialReader, SLOT(connect_ports()));
            connect(serialReader, SIGNAL(finished_Port()), IO_thread, SLOT(quit()));
            IO_thread->start();
        }
        else
        {
            if (serialReader != nullptr)
            {
                IO_thread->quit();
                delete serialReader;
                delete IO_thread;
                delete strToFloat;
            }
            IO_thread = new QThread();
            fileReader = new QFileIO(input_settings.getFileReader());
            fileReader->moveToThread(IO_thread);
            strToFloat = new StringToFloatMeasurements(fileReader);
            strToFloat->moveToThread(IO_thread);
            monitor_input.inputPtr(fileReader);
            connect(IO_thread, SIGNAL(started()), fileReader, SLOT(start_read()));
            connect(fileReader, SIGNAL(finished_File()), IO_thread, SLOT(quit()));
            IO_thread->start();
        }
        plot_monitor.input_ptrStF(strToFloat);
        qDebug() << QThread::currentThreadId();
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


void MainWindow::on_pushButton_clicked()
{
    bool ok;
    double phi = ui->lineEdit->text().toDouble(&ok);
    if (!ok) return;
    double lambda = ui->lineEdit_2->text().toDouble(&ok);
    if (!ok) return;
    double psi = ui->lineEdit_4->text().toDouble(&ok);
    if (!ok) return;
    ui->comboBox->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
    ui->lineEdit_4->setEnabled(false);
    process_method = ui->comboBox->currentIndex();
    switch (process_method)
    {
    case 0:
        ProcessThread = new QThread();
        Block1 = new OrientationAlgorithm();
        Block2 = new NavigationAlgorithm();
        Block3 = new GeoAngularVelocityVector();
        serial_process = new SerialProcessThread();
        serial_process->input_Blocks(Block1, Block2, Block3, strToFloat);
        serial_process->moveToThread(ProcessThread);
        connect(ProcessThread, SIGNAL(started()), serial_process, SLOT(serial_process()));
        connect(serial_process, SIGNAL(finished_process()), ProcessThread, SLOT(quit()));
        break;
    case 1:
        ProcessThread = new QThread();
        Block1 = new OrientationAlgorithmParallel();
        Block2 = new NavigationAlgorithmParallel();
        Block3 = new GeoAngularVelocityVector();
        serial_process = new SerialProcessThread();
        serial_process->input_Blocks(Block1, Block2, Block3, strToFloat);
        serial_process->moveToThread(ProcessThread);
        connect(ProcessThread, SIGNAL(started()), serial_process, SLOT(serial_process()));
        connect(serial_process, SIGNAL(finished_process()), ProcessThread, SLOT(quit()));
        break;
    case 2:
        ProcessThread = new QThread();
        Block1 = new OrientationAlgorithm();
        Block2 = new NavigationAlgorithm();
        Block3 = new GeoAngularVelocityVector();
        parallel_process = new ParallelProcessThread();
        parallel_process->input_Blocks(Block1, Block2, Block3, strToFloat);
        parallel_process->moveToThread(ProcessThread);
        connect(ProcessThread, SIGNAL(started()), parallel_process, SLOT(init_Blocks()));
        connect(parallel_process, SIGNAL(finished_thread()), ProcessThread, SLOT(quit()));
        break;
    case 3:
        ProcessThread = new QThread();
        Block1 = new OrientationAlgorithmParallel();
        Block2 = new NavigationAlgorithmParallel();
        Block3 = new GeoAngularVelocityVector();
        parallel_process = new ParallelProcessThread();
        parallel_process->input_Blocks(Block1, Block2, Block3, strToFloat);
        parallel_process->moveToThread(ProcessThread);
        connect(ProcessThread, SIGNAL(started()), parallel_process, SLOT(init_Blocks()));
        connect(parallel_process, SIGNAL(finished_thread()), ProcessThread, SLOT(quit()));
        break;
    }
    Block1->moveToThread(ProcessThread);
    Block2->moveToThread(ProcessThread);
    Block3->moveToThread(ProcessThread);
    Block1->input_psi(psi);
    Block2->input_Lambda(qDegreesToRadians(lambda));
    Block2->input_Phi(qDegreesToRadians(phi));
    Block3->input_diff_Lambda(Block2->get_diff_Lambda());
    Block3->input_diff_Phi(Block2->get_diff_Phi());
    Block3->input_Phi(Block2->get_Phi());
    Block3->calculate_OmegaGMatrix();
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
    table_matrix.input_C_Matrix(Block1->getC_Matrix());
    connect(Block1, SIGNAL(signalC_MatrixReady(QGenericMatrix <3,3,double>)), &table_matrix, SLOT(input_C_Matrix(QGenericMatrix <3,3,double>)));
    connect(Block1, SIGNAL(signalAnglesReady(std::array<double, 3>)), &table_matrix, SLOT(input_angles(std::array<double, 3>)));
    chart->axisX()->setRange(lambda-0.25, lambda+0.25);
    chart->axisY()->setRange(phi-0.25, phi+0.25);
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->comboBox->setEnabled(true);
    ui->lineEdit->setEnabled(true);
    ui->lineEdit_2->setEnabled(true);
    ui->lineEdit_4->setEnabled(true);
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    disconnect(Block1, SIGNAL(signalC_MatrixReady(QGenericMatrix <3,3,double>)), &table_matrix, SLOT(input_C_Matrix(QGenericMatrix <3,3,double>)));
    disconnect(Block1, SIGNAL(signalAnglesReady(std::array<double, 3>)), &table_matrix, SLOT(input_angles(std::array<double, 3>)));
    switch (process_method)
    {
    case 0:
        disconnect(ProcessThread, SIGNAL(started()), serial_process, SLOT(serial_process()));
        disconnect(serial_process, SIGNAL(finished_process()), ProcessThread, SLOT(quit()));
        delete Block1;
        delete Block2;
        delete Block3;
        delete ProcessThread;
        delete serial_process;
        break;
    case 1:
        disconnect(ProcessThread, SIGNAL(started()), serial_process, SLOT(serial_process()));
        disconnect(serial_process, SIGNAL(finished_process()), ProcessThread, SLOT(quit()));
        delete Block1;
        delete Block2;
        delete Block3;
        delete ProcessThread;
        delete serial_process;
        break;
    case 2:
        disconnect(ProcessThread, SIGNAL(started()), parallel_process, SLOT(init_Blocks()));
        disconnect(parallel_process, SIGNAL(finished_thread()), ProcessThread, SLOT(quit()));
        delete Block1;
        delete Block2;
        delete Block3;
        delete ProcessThread;
        delete parallel_process;
        break;
    case 3:
        break;
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(true);
    connect(strToFloat, SIGNAL(signalArrayReady()), serial_process, SLOT(serial_process()));
    connect(serial_process, SIGNAL(signalDataInput()), fileReader, SLOT(read_string()));
    connect(parallel_process, SIGNAL(signalDataInput()), fileReader, SLOT(read_string()));
    connect(Block2, SIGNAL(signalLambdaDegreesReady(double)), this, SLOT(input_lambda_lineedit(double)));
    connect(Block2, SIGNAL(signalPhiDegreesReady(double)), this, SLOT(input_phi_lineedit(double)));
    connect(Block2, SIGNAL(signalCoordinatesReady()), this, SLOT(draw_Graph()));
    connect(serial_process, SIGNAL(signalTime(int)), this, SLOT(draw_timegraph(int)));
    connect(parallel_process, SIGNAL(signalTime(int)), this, SLOT(draw_timegraph(int)));
    ProcessThread->start();
}


void MainWindow::on_pushButton_5_clicked()
{
    ProcessThread->quit();
    ProcessThread->wait();
    disconnect(strToFloat, SIGNAL(signalArrayReady()), serial_process, SLOT(serial_process()));
    disconnect(serial_process, SIGNAL(signalDataInput()), fileReader, SLOT(read_string()));
    disconnect(parallel_process, SIGNAL(signalDataInput()), fileReader, SLOT(read_string()));
    disconnect(Block2, SIGNAL(signalLambdaDegreesReady(double)), this, SLOT(input_lambda_lineedit(double)));
    disconnect(Block2, SIGNAL(signalPhiDegreesReady(double)), this, SLOT(input_phi_lineedit(double)));
    disconnect(serial_process, SIGNAL(signalTime(int)), this, SLOT(draw_timegraph(int)));
    disconnect(parallel_process, SIGNAL(signalTime(int)), this, SLOT(draw_timegraph(int)));
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
    ui->pushButton_5->setEnabled(false);
}


void MainWindow::input_lambda_lineedit(double inp)
{
    QString b = QString::number(inp);
    ui->lineEdit_2->setText(b);
}

void MainWindow::input_phi_lineedit(double inp)
{
    QString b = QString::number(inp);
    ui->lineEdit->setText(b);
}

void MainWindow::draw_Graph()
{
    track->append(qRadiansToDegrees(Block2->get_Lambda()),qRadiansToDegrees(Block2->get_Phi()));
    ui->graphicsView->repaint();
}

void MainWindow::draw_timegraph(int inp_time)
{
    average_time_series->append(aver_count, inp_time);
    aver_count++;
    if (average_time_series->count() > 100)
    {
        average_time_series->remove(0);
    }
    aver_time = (aver_time+inp_time)/2;
    ui->graphicsView_2->chart()->axisX()->setRange(aver_count-100, aver_count);
    QString b = QString::number(aver_time);
    ui->lineEdit_3->setText(b);
}

void MainWindow::on_action_C_triggered()
{
    table_matrix.show();
}

