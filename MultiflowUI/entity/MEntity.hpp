//
// Created by miku on 11/20/2023.
//

#pragma once

#include "entity/common.hpp"

#include <QString>
#include <QQmlPropertyMap>

struct MProperty {
    Q_GADGET
    Q_PROPERTY(QString name MEMBER name)
    Q_PROPERTY(QVariant type MEMBER type)
    Q_PROPERTY(QVariant value MEMBER value)
    Q_PROPERTY(QVariant extra MEMBER extra)
    Q_PROPERTY(QVariant associateValue MEMBER associateValue)
    Q_PROPERTY(bool isHighFrequency MEMBER isHighFrequency)

public:
    QString name;
    QVariant type;
    QVariant value;
    QVariant extra;
    QVariant associateValue{QVariant::fromValue(0)};
    bool isHighFrequency{false};
};

Q_DECLARE_METATYPE(MProperty)

class MEntity final : public QQmlPropertyMap {
    Q_OBJECT

public:
    explicit MEntity(QObject* parent = nullptr);

    MEntity(const MEntity& other);

    MEntity& operator=(const MEntity& other);

    static void copy(MEntity* dst, const MEntity* src);
};

Q_DECLARE_METATYPE(MEntity)
