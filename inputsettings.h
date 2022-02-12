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

private slots:
    void on_pushButton_clicked();

private:
    Ui::inputsettings *ui;
};

#endif // INPUTSETTINGS_H