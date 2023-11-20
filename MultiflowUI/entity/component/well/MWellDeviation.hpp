#pragma once

#include "MDeviationParameter.hpp"

#include "entity/common.hpp"

#include <QString>
#include <QUuid>
#include <QVariant>

//井斜数据
struct MWellDeviation {
    Q_GADGET

public:
    enum SurveyType { Vertical, TwoD, ThreeD };

    enum DependentPara { MD, TVD, Angle };

    Q_MEMBER_INIT(QString, id, QUuid::createUuid().toString())
    Q_MEMBER(QString, wellId)
    Q_MEMBER(double, measurePointMD)
    Q_MEMBER(double, measurePointTVD)
    Q_MEMBER(double, inclination)
    Q_MEMBER(double, azimuth)
    Q_MEMBER(double, displacementEW)
    Q_MEMBER(double, displacementNS)
    Q_MEMBER(double, dogleg)
    Q_MEMBER(double, closureHorizon)
    Q_MEMBER(double, closureAzimuth)
    Q_MEMBER(double, closureDispl)
    Q_MEMBER(QString, remark)
    Q_MEMBER_INIT(SurveyType, surVeytype, SurveyType::Vertical)
    Q_MEMBER_INIT(DependentPara, depType, DependentPara::MD)
    Q_MEMBER(double, wellHeadDpeth)
    Q_MEMBER(double, bottomDepth)
    Q_MEMBER(QString, calMedthod)
    Q_MEMBER(QList<MDeviationParameter>, parameters)
};

Q_DECLARE_METATYPE(MWellDeviation)
