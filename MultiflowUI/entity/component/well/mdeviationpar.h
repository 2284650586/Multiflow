#ifndef MDEVIATIONPAR_H
#define MDEVIATIONPAR_H


class MDeviationPar
{
public:
    MDeviationPar();
    MDeviationPar(double MD, double TVD, double horizontalDisplacement, double angle, double azimuth, double maxDog);

    double getMD() const;
    void setMD(double newMD);
    double getTVD() const;
    void setTVD(double newTVD);
    double getHorizontalDisplacement() const;
    void setHorizontalDisplacement(double newHorizontalDisplacement);
    double getAngle() const;
    void setAngle(double newAngle);
    double getAzimuth() const;
    void setAzimuth(double newAzimuth);
    double getMaxDog() const;
    void setMaxDog(double newMaxDog);

private:
    double MD;
    double TVD;
    double horizontalDisplacement;
    double angle;
    double azimuth;
    double maxDog;

};

#endif // MDEVIATIONPAR_H
