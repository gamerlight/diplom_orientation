#ifndef INPUTSETTINGS_H
#define INPUTSETTINGS_H

#include <QDialog>

namespace Ui {
class inputsettings;
}

class inputsettings : public QDialog
{
    Q_OBJECT

public:
    explicit inputsettings(QWidget *parent = nullptr);
    ~inputsettings();
    QString getPortNamestr_read();
    QString getPortNamestr_write();
    QString getFileReader();
    bool getInputMethod();

private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_2_clicked();

private:
    Ui::inputsettings *ui;
    QString fileReader;
    QString portNamestr_read;
    QString portNamestr_write;
    bool inputMethod;
};

#endif // INPUTSETTINGS_H
