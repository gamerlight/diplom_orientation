#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QThread>

#include "inputsettings.h"
#include "qserialio.h"
#include "qfileio.h"
#include "monitorinput.h"
#include "stringtofloatmeasurements.h"
#include "plotmonitor.h"
#include "orientationalgorithm.h"
#include "navigationalgorithm.h"
#include "orientationalgorithmparallel.h"
#include "navigationalgorithmparallel.h"
#include "geoangularvelocityvector.h"
#include "tablecmatrix.h"
#include "chartview.h"
#include "chart.h"
#include "serialprocessthread.h"
#include "parallelprocessthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *getMainWindow();

private slots:

    void input_lambda_lineedit(double);

    void input_phi_lineedit(double);

    void draw_Graph();

    void draw_timegraph(int);

    void on_action_triggered();

    void on_action_3_triggered();

    void on_action_2_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_action_C_triggered();

private:
    Ui::MainWindow *ui;

    QSerialIO *serialReader;
    QFileIO *fileReader;
    StringToFloatMeasurements *strToFloat;

    inputsettings input_settings;
    MonitorInput monitor_input;
    plotMonitor plot_monitor;
    TableCMatrix table_matrix;

    OrientationAlgorithm *Block1;
    NavigationAlgorithm *Block2;
    GeoAngularVelocityVector *Block3;

    QThread *ProcessThread;
    QThread *IO_thread;

    SerialProcessThread *serial_process;
    ParallelProcessThread *parallel_process;

    int process_method;
    int aver_time;
    int aver_count;

    Chart *chart;
    QSplineSeries *track;

    QSplineSeries *average_time_series;
};
#endif // MAINWINDOW_H
