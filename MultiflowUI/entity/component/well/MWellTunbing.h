#pragma once

#include "entity/common.hpp"

#include <QUuid>
#include <QString>
#include <QDateTime>

//油管库
struct MWellTunbing {
    Q_GADGET

public:
    Q_MEMBER_INIT(QString, id, QUuid::createUuid().toString()) // 唯一ID
    Q_MEMBER(double, innerDiameter) // 内直径(mm)
    Q_MEMBER(double, outDiameter) // 外直径(mm)
    Q_MEMBER(QString, materialId) // 材质唯一ID PDM_TO_MATERIAL表
    Q_MEMBER(double, specs) // 规格
    Q_MEMBER(double, perLengthWeight) // 公称重量 kg/m
    Q_MEMBER(double, collapsePress) // 抗挤强度(MPa) 挤毁压力
    Q_MEMBER(double, maxTensile) // 屈服强度(KN)
    Q_MEMBER(double, noumenonTensile) // 本体抗拉(kN)
    Q_MEMBER(double, connectionStrength) // 接头连线强度(kN)
    Q_MEMBER(QString, joinType) // 接头类型
    Q_MEMBER(double, driftDiameter) // 通径 mm
    Q_MEMBER(double, burstPress) // 内屈服压力(Mpa)
    Q_MEMBER(double, maxCTorque) // 抗扭强度
    Q_MEMBER(QString, factory) // 厂家
    Q_MEMBER(QString, model) // 型号
    Q_MEMBER(QString, sn) // 序列号
    Q_MEMBER(double, safeFactory) // 安全系数
    Q_MEMBER(double, perLengthDensity) // 线密度
    Q_MEMBER(double, elasticModule) // 弹性模量
    Q_MEMBER(QDateTime, createDate) // 创建时间
    Q_MEMBER(QString, createUser) // 创建用户
    Q_MEMBER(QDateTime, updateDate) // 修改时间
    Q_MEMBER(QString, updateUser) // 修改用户
    Q_MEMBER(QString, description) // 备注
    Q_MEMBER(QByteArray, icon) // 图片地址
    Q_MEMBER(double, poissonRatio) // 泊松比
    Q_MEMBER(QString, name) // 名称
    Q_MEMBER(double, roughness) // 摩擦系数
    Q_MEMBER(double, thermal) // 传热系数
    Q_MEMBER(double, toMD) // 深度
    Q_MEMBER(double, wallThickness) // 壁厚(mm)
    Q_MEMBER(QString, grade) // 钢级
    Q_MEMBER(double, density) // 密度(kg/m3)
    Q_MEMBER(double, ID)
    Q_MEMBER(QString, fluid)
    Q_MEMBER(double, fluidDensity)
    Q_MEMBER(double, fluidThermalCond)
};
