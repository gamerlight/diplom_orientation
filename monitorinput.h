#ifndef MONITORINPUT_H
#define MONITORINPUT_H

#include <QDialog>

#include "qserialio.h"
#include "qfileio.h"

namespace Ui {
class MonitorInput;
}

class MonitorInput : public QDialog
{
    Q_OBJECT

public:
    explicit MonitorInput(QWidget *parent = nullptr);
    ~MonitorInput();
    void inputPtr(QSerialIO *ptrr_serialReader);
    void inputPtr(QFileIO *ptrr_fileReader);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void input_TextEdit();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MonitorInput *ui;
    QSerialIO *ptr_serialReader = nullptr;
    QFileIO *ptr_fileReader = nullptr;
    bool monitor_init;
};

#endif // MONITORINPUT_H
