#pragma once

#include <QString>

class MSink {
public:
    //接收槽流量类型 Liquid:液体流量 Gas:气体流量 Mass:质量流量
    enum SinkType { Liquid, Gas, Mass };

    MSink();

    MSink(double sinkPressure, double sinkTemperature, SinkType sinkFlowType, double sinkFlowRate);

    [[nodiscard]] QString getSinkId() const;

    void setSinkId(const QString& newSinkId);

    [[nodiscard]] double getSinkPressure() const;

    void setSinkPressure(double newSinkPressure);

    [[nodiscard]] double getSinkTemperature() const;

    void setSinkTemperature(double newSinkTemperature);

    [[nodiscard]] SinkType getSinkFlowType() const { return sinkFlowType; }

    void setSinkFlowType(SinkType newSinkFlowType);

    [[nodiscard]] double getSinkFlowRate() const;

    void setSinkFlowRate(double newSinkFlowRate);

private:
    QString id; //接收槽ID
    double sinkPressure = 0; //接收槽压力    单位:Mpa a
    double sinkTemperature = 0; //接收槽温度    单位:DegC
    SinkType sinkFlowType; //接收槽流量类型
    double sinkFlowRate = 0; //接收槽流量    单位:sm^3
};
