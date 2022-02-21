#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>

#include "inputsettings.h"
#include "serialportmanager.h"
#include "qserialio.h"
#include "monitorinput.h"
#include "stringtofloatmeasurements.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_triggered();

    void on_action_3_triggered();

private:
    Ui::MainWindow *ui;
    SerialPortManager *serialManager;
    QSerialIO *serialReader;
    StringToFloatMeasurements *strToFloat;
    inputsettings input_settings;
    MonitorInput monitor_input;
};
#endif // MAINWINDOW_H
