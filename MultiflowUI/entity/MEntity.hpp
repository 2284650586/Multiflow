//
// Created by miku on 11/20/2023.
//

#pragma once

#include "entity/common.hpp"

#include <QVariant>
#include <QString>
#include <QMap>
#include <QMetaType>
#include <QQmlPropertyMap>

struct MProperty {
    Q_GADGET

public:
    Q_MEMBER(QString, name)
    Q_MEMBER(QVariant, type)
    Q_MEMBER(QVariant, value)
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
