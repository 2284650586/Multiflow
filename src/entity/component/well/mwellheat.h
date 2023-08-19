#ifndef MWELLHEAT_H
#define MWELLHEAT_H

#include <QList>
#include <QString>

class HTCCalculate
{

public:
    HTCCalculate(double MD, double groundDensity, double groundK, double groundCp);

    HTCCalculate(){}

    double getMD() const;
    void setMD(double newMD);
    double getGroundDensity() const;
    void setGroundDensity(double newGroundDensity);
    double getGroundK() const;
    void setGroundK(double newGroundK);
    double getGroundCp() const;
    void setGroundCp(double newGroundCp);

private:
    double MD;
    double groundDensity;
    double groundK;
    double groundCp;
};

class HTCCalATIMult {

public:
    HTCCalATIMult() {}

    HTCCalATIMult(double MD, double ambientTemperature, double groundDensity, double groundK, double gourndCp);

    double getMD() const;
    void setMD(double newMD);
    double getAmbientTemperature() const;
    void setAmbientTemperature(double newAmbientTemperature);
    double getGroundDensity() const;
    void setGroundDensity(double newGroundDensity);
    double getGroundK() const;
    void setGroundK(double newGroundK);
    double getGourndCp() const;
    void setGourndCp(double newGourndCp);

private:
    double MD;
    double ambientTemperature;
    double groundDensity;
    double groundK;
    double gourndCp;
};

class UMultATIMult {
public:
    UMultATIMult(double MD, double ambientTemperature, double UValue);

    UMultATIMult() {}

    double getMD() const;
    void setMD(double newMD);
    double getAmbientTemperature() const;
    void setAmbientTemperature(double newAmbientTemperature);
    double getUValue() const;
    void setUValue(double newUValue);

private:
    double MD;
    double ambientTemperature;
    double UValue;
};

class MWellHeat
{
public:
    MWellHeat();
    ~MWellHeat();

    QString getHeatTransferCoefficient() const;
    void setHeatTransferCoefficient(const QString &newHeatTransferCoefficient);
    QString getUValutInput() const;
    void setUValutInput(const QString &newUValutInput);
    double getAverageUValue() const;
    void setAverageUValue(double newAverageUValue);
    double getAmbientTemperatureInput() const;
    void setAmbientTemperatureInput(double newAmbientTemperatureInput);
    double getSoilTemperatureWellhead() const;
    void setSoilTemperatureWellhead(double newSoilTemperatureWellhead);
    double getTime() const;
    void setTime(double newTime);
    QList<HTCCalculate *> getHtcCalculateList() const;
    void setHtcCalculateList(const QList<HTCCalculate *> &newHtcCalculateList);
    QList<HTCCalATIMult *> getHtcCalATIMultList() const;
    void setHtcCalATIMultList(const QList<HTCCalATIMult *> &newHtcCalATIMultList);
    QList<UMultATIMult *> getUMultATIMultList() const;
    void setUMultATIMultList(const QList<UMultATIMult *> &newUMultATIMultList);

    void addHtcCal(HTCCalculate *para) {htcCalculateList.append(para);}
    void addHtcCalAtiMul(HTCCalATIMult *para) {htcCalATIMultList.append(para);}
    void addUMultAtiMul(UMultATIMult *para) {uMultATIMultList.append(para);}

    void clearHtcCalList(){qDeleteAll(htcCalculateList); htcCalculateList.clear();}
    void clearHtcCalAtiMultList(){qDeleteAll(htcCalATIMultList); htcCalATIMultList.clear();}
    void clearUMultAtiMultList(){qDeleteAll(uMultATIMultList); uMultATIMultList.clear();}


private:
    QString heatTransferCoefficient;        //Specify   Calculate
    QString UValutInput;                    //Single    Multiple
    double averageUValue;
    double ambientTemperatureInput;         //Single    Multiple
    double soilTemperatureWellhead;
    double time;
    QList<HTCCalculate*> htcCalculateList;
    QList<HTCCalATIMult*> htcCalATIMultList;
    QList<UMultATIMult*> uMultATIMultList;

};

#endif // MWELLHEAT_H
