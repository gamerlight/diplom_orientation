#include "plotmonitor.h"
#include "ui_plotmonitor.h"

plotMonitor::plotMonitor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::plotMonitor)
{
    connect(this, SIGNAL(signalBufferReady()), this, SLOT(draw_plot()));
    x = 0;
    y_1 = 0;
    y_2 = 0;
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
    y_1 = 0;
    y_2 = 0;
    ui->graphicsView->chart()->axisX()->setRange(0, 1000);
    ui->graphicsView_2->chart()->axisX()->setRange(0, 1000);
    ui->graphicsView->chart()->axisY()->setRange(-10, 10);
    ui->graphicsView_2->chart()->axisY()->setRange(-10, 10);
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
        disconnect(ptr_StringtoFloat, SIGNAL(signalArrayReady()), 0, 0);
    }
}


void plotMonitor::on_pushButton_3_clicked()
{
    this->accept();
}

void plotMonitor::input_accelgyro()
{
    accel_gyro = ptr_StringtoFloat->getAccel_gyro();
    emit signalBufferReady();
}

void plotMonitor::draw_plot()
{
    X_accel->append(x, accel_gyro[0]);
    Y_accel->append(x, accel_gyro[1]);
    Z_accel->append(x, accel_gyro[2]);
    X_gyro->append(x, accel_gyro[3]);
    Y_gyro->append(x, accel_gyro[4]);
    Z_gyro->append(x, accel_gyro[5]);
    for (int i = 0; i < 3; i++)
    {
        if (fabs(accel_gyro[i])> y_1)
        {
            y_1 = accel_gyro[i];
            ui->graphicsView->chart()->axisY()->setRange(-y_1, y_1);
        }
    }
    for (int i = 3; i < 6; i++)
    {
        if (fabs(accel_gyro[i])> y_2)
        {
            y_2 = accel_gyro[i];
            ui->graphicsView_2->chart()->axisY()->setRange(-y_2, y_2);
        }
    }
    if (X_accel->count()>15)
    {
        X_accel->remove(0);
        Y_accel->remove(0);
        Z_accel->remove(0);
        X_gyro->remove(0);
        Y_gyro->remove(0);
        Z_gyro->remove(0);
    }
    ui->graphicsView->chart()->axisX()->setRange(x-1000, x);
    ui->graphicsView_2->chart()->axisX()->setRange(x-1000, x);
    x += 100;
}

