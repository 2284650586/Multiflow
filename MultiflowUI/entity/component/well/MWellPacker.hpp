#pragma once

#include "entity/common.hpp"

#include <QDateTime>
#include <QString>
#include <QUuid>

//封隔器
struct MWellPacker {
    Q_GADGET

public:
    Q_MEMBER_INIT(QString, id, QUuid::createUuid().toString()) // 唯一ID
    Q_MEMBER(double, innerDiameter) // 内径（mm）
    Q_MEMBER(double, outDiameter) // 外径(mm)
    Q_MEMBER(QString, materialId) // 钢体材质唯一ID PDM_TO_MATERIAL表
    Q_MEMBER(QString, grade) // 钢级
    Q_MEMBER(double, length) // 长度
    Q_MEMBER(double, workPressureDiff) // 额定工作压差 Mpa
    Q_MEMBER(int, sealType) // 坐封方式 0 机械坐封、1 液压坐封
    Q_MEMBER(int, unsealType) // 解封方式
    Q_MEMBER(double, sealPressure) // 坐封压力 Mpa
    Q_MEMBER(double, workTemperature) // 工作温度℃
    Q_MEMBER(double, casingDiameter) // 适用套管内径mm
    Q_MEMBER(QString, boreMaterial) // 胶筒材质 PDM_TO_MATERIAL表
    Q_MEMBER(double, driftDiameter) // 通径 mm
    Q_MEMBER(double, perLengthWeight) // 线重量kg/m
    Q_MEMBER(double, collapsePressure) // 抗挤强度(KN)
    Q_MEMBER(double, maxTensile) // 屈服强度(KN)
    Q_MEMBER(double, burstPressure) // 内屈服强度(Mpa)
    Q_MEMBER(double, maxCTorque) // 抗扭强度
    Q_MEMBER(double, safetyFactor) // 安全系数
    Q_MEMBER(double, noumenonTensile) // 本体抗拉(KN)
    Q_MEMBER(int, waterAnchor) // 是否带水力锚
    Q_MEMBER(double, sealingDiameter) // 密封腔直径
    Q_MEMBER(double, maxCasingFriction) // 与套管最大的摩擦力(KN)
    Q_MEMBER(QString, factory) // 厂家
    Q_MEMBER(QString, model) // 型号
    Q_MEMBER(QString, sn) // 序列号
    Q_MEMBER(QDateTime, createDate) // 创建时间
    Q_MEMBER(QString, createUser) // 创建人
    Q_MEMBER(QDateTime, updateDate) // 修改时间
    Q_MEMBER(QString, updateUser) // 修改人
    Q_MEMBER(QString, description) // 备注
    Q_MEMBER(double, unsealingForce) // 解封力
    Q_MEMBER(QByteArray, icon) // 图片地址
    Q_MEMBER(double, measuredDepth) // 深度
    Q_MEMBER(QString, name) // 名称
};
