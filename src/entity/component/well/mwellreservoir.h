#ifndef MWELLRESERVOIR_H
#define MWELLRESERVOIR_H
#include <QString>

//Reservoir数据
class MWellReservoir
{
public:
    //流体类型
    enum ReservoirFluidType { Liquid, Gas, Mass };
    MWellReservoir();
    MWellReservoir(ReservoirFluidType fluidType, double fluidDensity, double fluidViscosity, double reservoirPressure, double reservoirTemperature, double reservoirWatercut);

    QString getId() const;
    void setId(const QString &newId);
    QString getWellId() const;
    void setWellId(const QString &newWellId);
    ReservoirFluidType getFluidType() const;
    void setFluidType(ReservoirFluidType newFluidType);
    double getFluidDensity() const;
    void setFluidDensity(double newFluidDensity);
    double getFluidViscosity() const;
    void setFluidViscosity(double newFluidViscosity);
    double getReservoirPressure() const;
    void setReservoirPressure(double newReservoirPressure);
    double getReservoirTemperature() const;
    void setReservoirTemperature(double newReservoirTemperature);
    double getReservoirWatercut() const;
    void setReservoirWatercut(double newReservoirWatercut);

private:
    QString id;
    QString wellId;
    ReservoirFluidType fluidType;   //流体类型
    double fluidDensity;            //流体密度  Kg/m^3
    double fluidViscosity;          //流体粘度  MPa · s
    double reservoirPressure;       //油藏压力  MPa a
    double reservoirTemperature;    //油藏温度  DegC
    double reservoirWatercut;       //油藏含水量 &
};

#endif // MWELLRESERVOIR_H
