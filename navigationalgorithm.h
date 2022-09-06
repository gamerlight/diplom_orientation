#ifndef NAVIGATIONALGORITHM_H
#define NAVIGATIONALGORITHM_H

#include <QGenericMatrix>
#include <QObject>


class NavigationAlgorithm : public QObject
{
    Q_OBJECT
public:
    NavigationAlgorithm();
    void input_Lambda(double);
    void input_Phi(double);
    void input_accel_array();   
    double get_Lambda();
    double get_Phi();
    double get_diff_Lambda();
    double get_diff_Phi();
public slots:
    void input_accel_array(std::array<double, 3>);
    void input_C_Matrix(QGenericMatrix <3,3,double>);
    virtual void calculate_coordinates();

signals:
    void signalLambdaReady(double sig_lambda);
    void signalLambdaDegreesReady(double sig_lambda);
    void signalPhiReady(double sig_phi);
    void signalCoordinatesReady();
    void signalPhiDegreesReady(double sig_phi);
    void signaldiff_LambdaReady(double sig_diff_lambda);
    void signaldiff_PhiReady(double sig_diff_phi);
    void signalStartCalculate();

protected:
    QGenericMatrix <3,3,double> С_Matrix;
    QGenericMatrix <1,3,double> accel_array;
    QGenericMatrix <1,3,double> ng_array;
    double radius_Earth = 6371000;
    double Lambda;
    double Phi;
    double diff_Lambda = 0;
    double diff_Phi = 0;
    double Vx = 0;
    double Vy = 0;
    double Vz = 0;
    virtual void calculate_nx_ny_nz();
    double calculate_generationblock_ax();
    double calculate_generationblock_ay();
    double calculate_generationblock_az();
    void calculate_longitude();   //Долгота
    void calculate_latitude();    //Широта   
};

#endif // NAVIGATIONALGORITHM_H
