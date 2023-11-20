#pragma once

#include "component/flowline/MFlowlineParameter.hpp"

#include <QString>
#include <QList>
#include <QUuid>


struct MFlowline {
    //流动类型  Pipe:管道流动  Annulus:环形空间流动
    enum FlowlineType { Pipe, Annulus };

    //管线模式
    enum FlowlineMode { Simple, Detailed };

    //管线环境  Land:陆地管线  Subsea:海底管线
    enum FlowlineEnviroment { Land, Subsea };

    QString id{QUuid::createUuid().toString()}; //出油管ID
    FlowlineType flowlineType; //流动类型
    FlowlineMode flowlineMode; //管线模式
    FlowlineEnviroment flowlineEnviroment; //管线环境
    double pipInsideDiameter{0}; //管道内径      单位:mm
    double pipWallThickness{0}; //管道壁厚      单位:mm
    double pipeRoughness{0}; //管道粗糙度    单位:mm
    double profileHorizontalDistance{0}; //水平距离      单位:Km
    double profileElevatiaonDifference{0}; //高程差        单位：Km
    double heatTransferCoefficient{0}; //传导系数      单位:J/(s.degC.m^2)
    QList<MFlowlineParameter> parameters;
};
