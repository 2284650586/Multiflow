#pragma once

#include <QString>
#include <QUuid>

struct MSource {
    //源流量类型 Liquid:液体流量 Gas:气体流量 Mass:质量流量
    enum SourceType { Liquid, Gas, Mass };

    QString id{QUuid::createUuid().toString()}; //源ID
    double sourcePressure = 0; //源压力     单位:Mpa a
    double sourceTemperature = 0; //源温度     单位:DegC
    SourceType sourceFlowType; //源流动类型
    double sourceFlowRate = 0; //源流动流量  单位:sm^3
};
