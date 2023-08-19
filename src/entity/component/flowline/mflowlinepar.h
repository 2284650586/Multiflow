#ifndef MFLOWLINEPAR_H
#define MFLOWLINEPAR_H


class MFlowlinePar
{
public:
    MFlowlinePar();
    MFlowlinePar(double hd1, double elevation, double hd2, double temperature);


    double getHd1() const;
    void setHd1(double newHd1);
    double getElevation() const;
    void setElevation(double newElevation);
    double getHd2() const;
    void setHd2(double newHd2);
    double getTemperature() const;
    void setTemperature(double newTemperature);

private:
    double hd1;
    double elevation;
    double hd2;
    double temperature;

};

#endif // MFLOWLINEPAR_H
