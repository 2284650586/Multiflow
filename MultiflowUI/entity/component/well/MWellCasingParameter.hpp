#pragma once

#include <QString>
#include <QDateTime>

// 套管库
class MWellCasingParameter {
public:
    MWellCasingParameter();

    QString getId() const;

    void setId(const QString& newId);

    QString getName() const;

    void setName(const QString& newName);

    double getInnerDiameter() const;

    void setInnerDiameter(double newInnerDiameter);

    double getOutDiameter() const;

    void setOutDiameter(double newOutDiameter);

    QString getMaterialId() const;

    void setMaterialId(const QString& newMaterialId);

    QString getGrade() const;

    void setGrade(const QString& newGrade);

    double getPerLengthWeight() const;

    void setPerLengthWeight(double newPerLengthWeight);

    QString getEndFace() const;

    void setEndFace(const QString& newEndFace);

    double getDensity() const;

    void setDensity(double newDensity);

    double getAdjPerLengthWeight() const;

    void setAdjPerLengthWeight(double newAdjPerLengthWeight);

    double getJointOutDiameter() const;

    void setJointOutDiameter(double newJointOutDiameter);

    double getJointInnerDiameter() const;

    void setJointInnerDiameter(double newJointInnerDiameter);

    double getJointTensile() const;

    void setJointTensile(double newJointTensile);

    double getNoumenonTensile() const;

    void setNoumenonTensile(double newNoumenonTensile);

    double getBuckleTorque() const;

    void setBuckleTorque(double newBuckleTorque);

    int getElasticModulus() const;

    void setElasticModulus(int newElasticModulus);

    double getWallThickness() const;

    void setWallThickness(double newWallThickness);

    double getCollapsePressure() const;

    void setCollapsePressure(double newCollapsePressure);

    double getMaxCTorque() const;

    void setMaxCTorque(double newMaxCTorque);

    double getBurstPressure() const;

    void setBurstPressure(double newBurstPressure);

    double getMaxTensile() const;

    void setMaxTensile(double newMaxTensile);

    double getDriftDiameter() const;

    void setDriftDiameter(double newDriftDiameter);

    double getSafetyFactor() const;

    void setSafetyFactor(double newSafetyFactor);

    QString getFactory() const;

    void setFactory(const QString& newFactory);

    QString getModel() const;

    void setModel(const QString& newModel);

    QString getSn() const;

    void setSn(const QString& newSn);

    QDateTime getCreateDate() const;

    void setCreateDate(const QDateTime& newCreateDate);

    QString getCreateUser() const;

    void setCreateUser(const QString& newCreateUser);

    QString getDescription() const;

    void setDescription(const QString& newDescription);

    QDateTime getUpdateDate() const;

    void setUpdateDate(const QDateTime& newUpdateDate);

    QString getUpdateUser() const;

    void setUpdateUser(const QString& newUpdateUser);

    QByteArray getIcon() const;

    void setIcon(const QByteArray& newIcon);

    double getToMD() const;

    void setToMD(double newToMD);

    double getRoughness() const;

    void setRoughness(double newRoughness);

    double getThermal() const;

    void setThermal(double newThermal);

    double getCementTop() const;

    void setCementTop(double newCementTop);

    double getCementDensity() const;

    void setCementDensity(double newCementDensity);

    double getCementTheramlCond() const;

    void setCementTheramlCond(double newCementTheramlCond);

private:
    QString id; // 唯一ID
    double innerDiameter; // 内径(mm)
    double outDiameter; // 外径(mm)
    QString materialId; // 材质唯一ID PDM_TO_MATERIAL表
    double perLengthWeight; // 名义线重(kg/m)
    QString endFace; // 端面
    double adjPerLengthWeight; // 调整线重(kg/m)
    double jointOutDiameter; // 接头外径(mm)
    double jointInnerDiameter; // 接头内径(mm)
    double jointTensile; // 接头抗拉(KN)
    double noumenonTensile; // 本体抗拉(KN)
    double buckleTorque; // 上扣扭矩(Nm)
    int elasticModulus; // 弹性模量(MPa)
    double collapsePressure; // 抗挤强度(MPa)
    double maxCTorque; // 抗扭强度
    double burstPressure; // 抗内压强度(MPa)
    double maxTensile; // 屈服强度(KN)
    double driftDiameter; // 通径 mm
    double safetyFactor; // 安全系数
    QString factory; // 厂家
    QString model; // 型号
    QString sn; // 序列号
    QDateTime createDate; // 创建时间
    QString createUser; // 创建用户
    QString description; // 备注
    QDateTime updateDate; // 修改时间
    QString updateUser; // 修改用户
    QByteArray icon; // 图片地址

    QString name; // 名字
    double wallThickness; // 壁厚(mm)
    QString grade; // 钢级
    double density; // 密度(kg/m3)
    double toMD;
    double ID;
    double roughness;
    double thermal;
    double cementTop;
    double cementDensity;
    double cementTheramlCond;
};
