#pragma once

#include <QString>
#include <QUuid>

struct MSink {
    //接收槽流量类型 Liquid:液体流量 Gas:气体流量 Mass:质量流量
    enum SinkType { Liquid, Gas, Mass };

    QString id{QUuid::createUuid().toString()}; //接收槽ID
    double sinkPressure = 0; //接收槽压力    单位:Mpa a
    double sinkTemperature = 0; //接收槽温度    单位:DegC
    SinkType sinkFlowType; //接收槽流量类型
    double sinkFlowRate = 0; //接收槽流量    单位:sm^3
};
