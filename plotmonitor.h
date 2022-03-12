#ifndef PLOTMONITOR_H
#define PLOTMONITOR_H

#include <QDialog>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>

#include <array>

#include "stringtofloatmeasurements.h"

namespace Ui {
class plotMonitor;
}

class plotMonitor : public QDialog
{
    Q_OBJECT

public:
    explicit plotMonitor(QWidget *parent = nullptr);
    ~plotMonitor();

public slots:
    void input_ptrStF(StringToFloatMeasurements*);

signals:
    void signalBufferReady();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void input_accelgyro();

    void draw_plot();

private:
    Ui::plotMonitor *ui;
    StringToFloatMeasurements *ptr_StringtoFloat;
    bool monitor_init;
    std::array<float, 6> accel_gyro;
    QSplineSeries *X_accel;
    QSplineSeries *Y_accel;
    QSplineSeries *Z_accel;
    QSplineSeries *X_gyro;
    QSplineSeries *Y_gyro;
    QSplineSeries *Z_gyro;
    float x;
    float y_1;
    float y_2;
};

#endif // PLOTMONITOR_H
