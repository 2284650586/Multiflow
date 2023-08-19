#ifndef MFLOWLINE_H
#define MFLOWLINE_H
#include <QString>
#include <QList>
#include "component/flowline/mflowlinepar.h"


class MFlowline
{
public:
    //流动类型  Pipe:管道流动  Annulus:环形空间流动
    enum FlowlineType { Pipe, Annulus};
    //管线模式
    enum FlowlineMode { Simple, Detailed };
    //管线环境  Land:陆地管线  Subsea:海底管线
    enum FlowlineEnviroment { Land, Subsea };
    MFlowline();
    MFlowline(FlowlineType flowlineType, FlowlineMode flowlineMode, FlowlineEnviroment flowlineEnviroment, double pipInsideDiameter, double pipWallThickness, double pipeRoughness, double profileHorizontalDistance, double profileElevatiaonDifference, double heatTransferCoefficient);
    ~MFlowline();

    QString getFlowlineId() const;
    void setFlowlineId(const QString &newFlowlineId);
    FlowlineType getFlowlineType() const;
    void setFlowlineType(FlowlineType newFlowlineType);
    FlowlineMode getFlowlineMode() const;
    void setFlowlineMode(FlowlineMode newFlowlineMode);
    FlowlineEnviroment getFlowlineEnviroment() const;
    void setFlowlineEnviroment(FlowlineEnviroment newFlowlineEnviroment);
    double getPipInsideDiameter() const;
    void setPipInsideDiameter(double newPipInsideDiameter);
    double getPipWallThickness() const;
    void setPipWallThickness(double newPipWallThickness);
    double getPipeRoughness() const;
    void setPipeRoughness(double newPipeRoughness);
    double getProfileHorizontalDistance() const;
    void setProfileHorizontalDistance(double newProfileHorizontalDistance);
    double getProfileElevatiaonDifference() const;
    void setProfileElevatiaonDifference(double newProfileElevatiaonDifference);
    double getHeatTransferCoefficient() const;
    void setHeatTransferCoefficient(double newHeatTransferCoefficient);

    void addPar(MFlowlinePar *par) { parList.append(par); }
    void addPar(double hd1, double elevation, double dh2, double temperature);

    void clearPar() { parList.clear(); }

    int getParCount() { return parList.count(); }

    QList<MFlowlinePar *> getParList() const;

private:
    QString id;                                 //出油管ID
    FlowlineType flowlineType;                  //流动类型
    FlowlineMode flowlineMode;                  //管线模式
    FlowlineEnviroment flowlineEnviroment;      //管线环境
    double pipInsideDiameter = 0;                   //管道内径      单位:mm
    double pipWallThickness = 0;                    //管道壁厚      单位:mm
    double pipeRoughness = 0;                       //管道粗糙度    单位:mm
    double profileHorizontalDistance = 0;           //水平距离      单位:Km
    double profileElevatiaonDifference = 0;         //高程差        单位：Km
    double heatTransferCoefficient = 0;             //传导系数      单位:J/(s.degC.m^2)

    QList<MFlowlinePar*> parList;


};

#endif // MFLOWLINE_H
