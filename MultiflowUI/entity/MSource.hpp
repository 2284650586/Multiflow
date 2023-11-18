#pragma once

#include <QString>

class MSource {
public:
    //源流量类型 Liquid:液体流量 Gas:气体流量 Mass:质量流量
    enum SourceType { Liquid, Gas, Mass };

    MSource();

    MSource(double sourcePressure, double sourceTemperature, SourceType sourceFlowType, double sourceFlowRate);


    QString getSourceId() const { return id; }

    double getSourcePressure() const;

    void setSourcePressure(double newSourcePressure);

    double getSourceTemperature() const;

    void setSourceTemperature(double newSourceTemperature);

    SourceType getSourceFlowType() const { return sourceFlowType; };

    void setSourceFlowType(SourceType newSourceFlowType);

    double getSourceFlowRate() const;

    void setSourceFlowRate(double newSourceFlowRate);

private:
    QString id; //源ID
    double sourcePressure = 0; //源压力     单位:Mpa a
    double sourceTemperature = 0; //源温度     单位:DegC
    SourceType sourceFlowType; //源流动类型
    double sourceFlowRate = 0; //源流动流量  单位:sm^3
};
