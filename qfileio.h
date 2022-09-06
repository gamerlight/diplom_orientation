#ifndef QFILEIO_H
#define QFILEIO_H

#include <QFile>
#include <QObject>

class QFileIO : public QObject
{
    Q_OBJECT
public:
    explicit QFileIO(QObject *parent = nullptr);
    QFileIO(QString, QObject *parent = nullptr);
    void input_filePath(QString);
    QString getDatastring();
    ~QFileIO();

public slots:
    void start_read();
    void read_string();

signals:
    void signalStringReady();
    void finished_File();

private:
    QString filePath;
    QFile file;
    QString data_string;
    QByteArray data_array;
};

#endif // QFILEIO_H
