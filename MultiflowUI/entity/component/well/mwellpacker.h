#ifndef MWELLPACKER_H
#define MWELLPACKER_H
#include <QDateTime>
#include <QString>

//封隔器
class MWellPacker
{
public:
    MWellPacker();
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
    double getLength() const;
    void setLength(double newLength);
    double getWorkPressureDiff() const;
    void setWorkPressureDiff(double newWorkPressureDiff);
    int getSealType() const;
    void setSealType(int newSealType);
    int getUnsealType() const;
    void setUnsealType(int newUnsealType);
    double getSealPressure() const;
    void setSealPressure(double newSealPressure);
    double getWorkTemperature() const;
    void setWorkTemperature(double newWorkTemperature);
    double getCasingDiameter() const;
    void setCasingDiameter(double newCasingDiameter);
    QString getBoreMaterial() const;
    void setBoreMaterial(const QString &newBoreMaterial);
    double getDriftDiameter() const;
    void setDriftDiameter(double newDriftDiameter);
    double getPerLengthWeight() const;
    void setPerLengthWeight(double newPerLengthWeight);
    double getCollapsePressure() const;
    void setCollapsePressure(double newCollapsePressure);
    double getMaxTensile() const;
    void setMaxTensile(double newMaxTensile);
    double getBurstPressure() const;
    void setBurstPressure(double newBurstPressure);
    double getMaxCTorque() const;
    void setMaxCTorque(double newMaxCTorque);
    double getSafetyFactor() const;
    void setSafetyFactor(double newSafetyFactor);
    double getNoumenonTensile() const;
    void setNoumenonTensile(double newNoumenonTensile);
    int getWaterAnchor() const;
    void setWaterAnchor(int newWaterAnchor);
    double getSealingDiameter() const;
    void setSealingDiameter(double newSealingDiameter);
    double getMaxCasingFriction() const;
    void setMaxCasingFriction(double newMaxCasingFriction);
    QString getFactory() const;
    void setFactory(const QString &newFactory);
    QString getModel() const;
    void setModel(const QString &newModel);
    QString getSn() const;
    void setSn(const QString &newSn);
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
    double getUnsealingForce() const;
    void setUnsealingForce(double newUnsealingForce);
    QByteArray getIcon() const;
    void setIcon(const QByteArray &newIcon);

    double getMeasuredDepth() const;
    void setMeasuredDepth(double newMeasuredDepth);

private:
    QString id;                   // 唯一ID
    double innerDiameter;         // 内径（mm）
    double outDiameter;           // 外径(mm)
    QString materialId;           // 钢体材质唯一ID PDM_TO_MATERIAL表
    QString grade;                // 钢级
    double length;                // 长度
    double workPressureDiff;      // 额定工作压差 Mpa
    int sealType;                 // 坐封方式 0 机械坐封、1 液压坐封
    int unsealType;               // 解封方式
    double sealPressure;          // 坐封压力 Mpa
    double workTemperature;       // 工作温度℃
    double casingDiameter;        // 适用套管内径mm
    QString boreMaterial;         // 胶筒材质 PDM_TO_MATERIAL表
    double driftDiameter;         // 通径 mm
    double perLengthWeight;       // 线重量kg/m
    double collapsePressure;      // 抗挤强度(KN)
    double maxTensile;            // 屈服强度(KN)
    double burstPressure;         // 内屈服强度(Mpa)
    double maxCTorque;            // 抗扭强度
    double safetyFactor;          // 安全系数
    double noumenonTensile;       // 本体抗拉(KN)
    int waterAnchor;              // 是否带水力锚
    double sealingDiameter;       // 密封腔直径
    double maxCasingFriction;     // 与套管最大的摩擦力(KN)
    QString factory;              // 厂家
    QString model;                // 型号
    QString sn;                   // 序列号
    QDateTime createDate;         // 创建时间
    QString createUser;           // 创建人
    QDateTime updateDate;         // 修改时间
    QString updateUser;           // 修改人
    QString description;          // 备注
    double unsealingForce;        // 解封力
    QByteArray icon;              // 图片地址

    double measuredDepth;         // 深度
    QString name;                 // 名称
};

#endif // MWELLPACKER_H
