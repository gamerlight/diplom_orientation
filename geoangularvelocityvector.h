#ifndef GEOANGULARVELOCITYVECTOR_H
#define GEOANGULARVELOCITYVECTOR_H

#include <QGenericMatrix>
#include <QObject>

class GeoAngularVelocityVector : public QObject
{
    Q_OBJECT
public:
    GeoAngularVelocityVector();
    QGenericMatrix <3,3,double> get_OmegaGMatrix();

public slots:
    void input_Phi(double);
    void input_diff_Lambda(double);
    void input_diff_Phi(double);
    void calculate_OmegaGMatrix();

signals:
    void signalOmegaGMatrix(QGenericMatrix <3,3,double>);
    void signalStartCalculate();

private:
    double Phi;
    double diff_Lambda = 0;
    double diff_Phi = 0;
    QGenericMatrix <3,3,double> OmegaGMatrix;
};

#endif // GEOANGULARVELOCITYVECTOR_H
