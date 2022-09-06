#include "plotmonitor.h"
#include "ui_plotmonitor.h"

plotMonitor::plotMonitor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::plotMonitor)
{
    connect(this, SIGNAL(signalBufferReady()), this, SLOT(draw_plot()));
    x = 0;
    y_1 = 10;
    y_2 = 5;
    tick_y_1 = 0;
    tick_y_2 = 0;
    ui->setupUi(this);
    ptr_StringtoFloat = nullptr;
    monitor_init = 0;
    X_accel = new QSplineSeries();
    Y_accel = new QSplineSeries();
    Z_accel = new QSplineSeries();
    X_accel->setName("X_accel");
    Y_accel->setName("Y_accel");
    Z_accel->setName("Z_accel");
    ui->graphicsView->chart()->addSeries(X_accel);
    ui->graphicsView->chart()->addSeries(Y_accel);
    ui->graphicsView->chart()->addSeries(Z_accel);
    ui->graphicsView->chart()->createDefaultAxes();
    X_gyro = new QSplineSeries();
    Y_gyro = new QSplineSeries();
    Z_gyro = new QSplineSeries();
    X_gyro->setName("X_gyro");
    Y_gyro->setName("Y_gyro");
    Z_gyro->setName("Z_gyro");
    ui->graphicsView_2->chart()->addSeries(X_gyro);
    ui->graphicsView_2->chart()->addSeries(Y_gyro);
    ui->graphicsView_2->chart()->addSeries(Z_gyro);
    ui->graphicsView_2->chart()->createDefaultAxes();
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_2->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->chart()->axisX()->setRange(0, 1000);
    ui->graphicsView_2->chart()->axisX()->setRange(0, 1000);
    ui->graphicsView->chart()->axisY()->setRange(-10, 10);
    ui->graphicsView_2->chart()->axisY()->setRange(-5, 5);
}

plotMonitor::~plotMonitor()
{
    delete X_accel;
    delete Y_accel;
    delete Z_accel;
    delete X_gyro;
    delete Y_gyro;
    delete Z_gyro;
    delete ui;
}

void plotMonitor::input_ptrStF(StringToFloatMeasurements *ptr)
{
    ptr_StringtoFloat = ptr;
}

void plotMonitor::on_pushButton_clicked()
{
    X_accel->clear();
    Y_accel->clear();
    Z_accel->clear();
    X_gyro->clear();
    Y_gyro->clear();
    Z_gyro->clear();
    x = 0;
    y_1 = 10;
    y_2 = 5;
    tick_y_1 = 0;
    tick_y_2 = 0;
    ui->graphicsView->chart()->axisX()->setRange(0, 1000);
    ui->graphicsView_2->chart()->axisX()->setRange(0, 1000);
    ui->graphicsView->chart()->axisY()->setRange(-10, 10);
    ui->graphicsView_2->chart()->axisY()->setRange(-5, 5);
}


void plotMonitor::on_pushButton_2_clicked()
{
    if (monitor_init == false)
    {
        monitor_init = true;
        connect(ptr_StringtoFloat, SIGNAL(signalArrayReady()), this, SLOT(input_accelgyro()));
    }
    else
    {
        monitor_init = false;
        disconnect(ptr_StringtoFloat, SIGNAL(signalArrayReady()), this, SLOT(input_accelgyro()));
    }
}


void plotMonitor::on_pushButton_3_clicked()
{
    this->accept();
}

void plotMonitor::input_accelgyro()
{
    accel = ptr_StringtoFloat->getAccel();
    gyro = ptr_StringtoFloat->getGyro();
    emit signalBufferReady();
}

void plotMonitor::draw_plot()
{
    X_accel->append(x, accel[0]);
    Y_accel->append(x, accel[1]);
    Z_accel->append(x, accel[2]);
    X_gyro->append(x, gyro[0]);
    Y_gyro->append(x, gyro[1]);
    Z_gyro->append(x, gyro[2]);
    tick_y_1++;
    for (int i = 0; i < 3; i++)
    {
        if (fabs(accel[i])+1 >= y_1)
        {
            y_1 = fabs(accel[i])+1;
            ui->graphicsView->chart()->axisY()->setRange(-y_1, y_1);
            tick_y_1 = 0;
        }
    }
    tick_y_2++;
    for (int i = 0; i < 3; i++)
    {
        if (fabs(gyro[i])+1 >= y_2)
        {
            y_2 = fabs(gyro[i])+1;
            ui->graphicsView_2->chart()->axisY()->setRange(-y_2, y_2);
            tick_y_2 = 0;
        }
    }
    if (X_accel->count()>20)
    {
        X_accel->remove(0);
        Y_accel->remove(0);
        Z_accel->remove(0);
        X_gyro->remove(0);
        Y_gyro->remove(0);
        Z_gyro->remove(0);
    }
    if (tick_y_1 > 10)
    {
        tick_y_1 = 0;
        y_1 -= 1;
        ui->graphicsView->chart()->axisY()->setRange(-y_1, y_1);
    }
    if (tick_y_2 > 10)
    {
        tick_y_2 = 0;
        y_2 -= 1;
        ui->graphicsView_2->chart()->axisY()->setRange(-y_2, y_2);
    }
    ui->graphicsView->chart()->axisX()->setRange(x-100, x);
    ui->graphicsView_2->chart()->axisX()->setRange(x-100, x);
    x += 5;
}

