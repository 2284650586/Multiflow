#ifndef MWELLTUNBING_H
#define MWELLTUNBING_H

#include <QString>
#include <QDateTime>

//油管库
class MWellTunbing
{
public:
    MWellTunbing();
    MWellTunbing(const QString &id, double innerDiameter, double outDiameter, const QString &materialId, double specs, double perLengthWeight, double collapsePress, double maxTensile, double noumenonTensile, double connectionStrength, const QString &joinType, double driftDiameter, double burstPress, double maxCTorque, const QString &factory, const QString &model, const QString &sn, double safeFactory, double perLengthDensity, double elasticModule, const QDateTime &createDate, const QString &createUser, const QDateTime &updateDate, const QString &updateUser, const QString &description, const QByteArray &icon, double poissonRatio, const QString &name, double roughness, double thermal, double toMD, double wallThickness, const QString &grade, double density, double ID, const QString &fluid, double fluidDensity, double fluidThermalCond);

    QString getId() const;
    void setId(const QString &newId);
    QString getName() const;
    void setName(const QString &newName);
    double getInnerDiameter() const;
    void setInnerDiameter(double newInnerDiameter);
    double getOutDiameter() const;
    void setOutDiameter(double newOutDiameter);
    QString getMaterialId() const;
    void setMaterialId(const QString &newMaterialId);
    QString getGrade() const;
    void setGrade(const QString &newGrade);
    double getWallThickness() const;
    void setWallThickness(double newWallThickness);
    double getSpecs() const;
    void setSpecs(double newSpecs);
    double getPerLengthWeight() const;
    void setPerLengthWeight(double newPerLengthWeight);
    double getCollapsePress() const;
    void setCollapsePress(double newCollapsePress);
    double getMaxTensile() const;
    void setMaxTensile(double newMaxTensile);
    double getNoumenonTensile() const;
    void setNoumenonTensile(double newNoumenonTensile);
    double getConnectionStrength() const;
    void setConnectionStrength(double newConnectionStrength);
    QString getJoinType() const;
    void setJoinType(const QString &newJoinType);
    double getDriftDiameter() const;
    void setDriftDiameter(double newDriftDiameter);
    double getBurstPress() const;
    void setBurstPress(double newBurstPress);
    double getMaxCTorque() const;
    void setMaxCTorque(double newMaxCTorque);
    QString getFactory() const;
    void setFactory(const QString &newFactory);
    QString getModel() const;
    void setModel(const QString &newModel);
    QString getSn() const;
    void setSn(const QString &newSn);
    double getSafeFactory() const;
    void setSafeFactory(double newSafeFactory);
    double getPerLengthDensity() const;
    void setPerLengthDensity(double newPerLengthDensity);
    double getDensity() const;
    void setDensity(double newDensity);
    double getElasticModule() const;
    void setElasticModule(double newElasticModule);
    QDateTime getCreateDate() const;
    void setCreateDate(const QDateTime &newCreateDate);
    QString getCreateUser() const;
    void setCreateUser(const QString &newCreateUser);
    QDateTime getUpdateDate() const;
    void setUpdateDate(const QDateTime &newUpdateDate);
    QString getUpdateUser() const;
    void setUpdateUser(const QString &newUpdateUser);
    QString getDescription() const;
    void setDescription(const QString &newDescription);
    double getPoissonRatio() const;
    void setPoissonRatio(double newPoissonRatio);
    double getRubModulus() const;
    void setRubModulus(double newRubModulus);
    QByteArray getIcon() const;
    void setIcon(const QByteArray &newIcon);

    double getRoughness() const;
    void setRoughness(double newRoughness);
    double getThermal() const;
    void setThermal(double newThermal);
    double getToMD() const;
    void setToMD(double newToMD);
    QString getFluidType() const;
    void setFluidType(const QString &newFluid);
    double getFluidDensity() const;
    void setFluidDensity(double newFluidDensity);
    double getFluidThermalCond() const;
    void setFluidThermalCond(double newFluidThermalCond);

private:
    QString id;                  // 唯一ID

    double innerDiameter;        // 内直径(mm)
    double outDiameter;          // 外直径(mm)
    QString materialId;          // 材质唯一ID PDM_TO_MATERIAL表

    double specs;                // 规格
    double perLengthWeight;      // 公称重量 kg/m
    double collapsePress;        // 抗挤强度(MPa) 挤毁压力
    double maxTensile;           // 屈服强度(KN)
    double noumenonTensile;      // 本体抗拉(kN)
    double connectionStrength;   // 接头连线强度(kN)
    QString joinType;            // 接头类型
    double driftDiameter;        // 通径 mm
    double burstPress;           // 内屈服压力(Mpa)
    double maxCTorque;           // 抗扭强度
    QString factory;             // 厂家
    QString model;               // 型号
    QString sn;                  // 序列号
    double safeFactory;          // 安全系数
    double perLengthDensity;     // 线密度

    double elasticModule;        // 弹性模量
    QDateTime createDate;        // 创建时间
    QString createUser;          // 创建用户
    QDateTime updateDate;        // 修改时间
    QString updateUser;          // 修改用户
    QString description;         // 备注
    QByteArray icon;             // 图片地址
    double poissonRatio;         // 泊松比

    QString name;                // 名称
    double roughness;            // 摩擦系数
    double thermal;              // 传热系数
    double toMD;                 // 深度
    double wallThickness;        // 壁厚(mm)
    QString grade;               // 钢级
    double density;              // 密度(kg/m3)
    double ID;
    QString fluid;
    double fluidDensity;
    double fluidThermalCond;


};

#endif // MWELLTUNBING_H
