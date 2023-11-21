#pragma once

#include <QString>
#include <QUuid>

//Reservoir数据
struct MWellReservoir {
    //流体类型
    enum ReservoirFluidType { Liquid, Gas, Mass };

    const QString id{QUuid::createUuid().toString()};
    const QString wellId;
    const ReservoirFluidType fluidType; //流体类型
    const double fluidDensity; //流体密度  Kg/m^3
    const double fluidViscosity; //流体粘度  MPa · s
    const double reservoirPressure; //油藏压力  MPa a
    const double reservoirTemperature; //油藏温度  DegC
    const double reservoirWatercut; //油藏含水量 &
};
