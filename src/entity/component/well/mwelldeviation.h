#ifndef MWELLDEVIATION_H
#define MWELLDEVIATION_H
#include "entity/component/well/mdeviationpar.h"
#include <QList>
#include <QString>

//井斜数据
class MWellDeviation
{
public:

    enum SurveyType { Vertical, TwoD, ThreeD };
    enum DependentPara { MD, TVD, Angle };

    MWellDeviation();
    MWellDeviation(double measurePointMD, double measurePointTVD, double inclination, double azimuth, double displacementEW, double displacementNS, double dogleg, double closureHorizon, double closureAzimuth, double closureDispl);

    QString getId() const;
    void setId(const QString &newId);
    QString getWellId() const;
    void setWellId(const QString &newWellId);
    double getMeasurePointMD() const;
    void setMeasurePointMD(double newMeasurePointMD);
    double getMeasurePointTVD() const;
    void setMeasurePointTVD(double newMeasurePointTVD);
    double getInclination() const;
    void setInclination(double newInclination);
    double getAzimuth() const;
    void setAzimuth(double newAzimuth);
    double getDisplacementEW() const;
    void setDisplacementEW(double newDisplacementEW);
    double getDisplacementNS() const;
    void setDisplacementNS(double newDisplacementNS);
    double getDogleg() const;
    void setDogleg(double newDogleg);
    double getClosureHorizon() const;
    void setClosureHorizon(double newClosureHorizon);
    double getClosureAzimuth() const;
    void setClosureAzimuth(double newClosureAzimuth);
    double getClosureDispl() const;
    void setClosureDispl(double newClosureDispl);
    QString getRemark() const;
    void setRemark(const QString &newRemark);

    double getWellHeadDpeth() const;
    void setWellHeadDpeth(double newWellHeadDpeth);

    SurveyType getSurVeytype() const;
    void setSurVeytype(SurveyType newSurVeytype);
    DependentPara getDepType() const;
    void setDepType(DependentPara newDepType);
    double getBottomDepth() const;
    void setBottomDepth(double newBottomDepth);
    QString getCalMedthod() const;
    void setCalMedthod(const QString &newCalMedthod);

    void clearPar() { parList.clear(); }
    int getParCount() { return parList.count(); }
    QList<MDeviationPar *> getParList() const;
    void addPar(MDeviationPar *par) { parList.append(par); }

private:
    QString id;                 //井斜id
    QString wellId;             //井id
    double measurePointMD;      //测点斜深
    double measurePointTVD;     //测点垂深
    double inclination;         //井斜角
    double azimuth;             //方位角
    double displacementEW;      //东西位移
    double displacementNS;      //南北位移
    double dogleg;              //狗腿度
    double closureHorizon;      //水平位移
    double closureAzimuth;      //闭合方位
    double closureDispl;        //闭合距
    QString remark;             //备注
    SurveyType surVeytype;
    DependentPara depType;
    double wellHeadDpeth;       //深度
    double bottomDepth;         //底深
    QString calMedthod;         //计算方法

    QList<MDeviationPar*> parList;

};

#endif // MWELLDEVIATION_H
