//
// Created by miku on 11/20/2023.
//

#pragma once

#include <QString>
#include <QQmlPropertyMap>

class MEntity final : public QQmlPropertyMap {
    Q_OBJECT

public:
    explicit MEntity(QObject* parent = nullptr);

    MEntity(const MEntity& other);

    MEntity& operator=(const MEntity& other);

    [[nodiscard]] QVariant get(const QString& key) const;

    static void copy(MEntity* dst, const MEntity* src);
};

Q_DECLARE_METATYPE(MEntity)

struct MProperty {
    Q_GADGET
    Q_PROPERTY(QString name MEMBER name)
    Q_PROPERTY(QVariant type MEMBER type)
    Q_PROPERTY(QVariant value MEMBER value)
    Q_PROPERTY(QVariant extra MEMBER extra)
    Q_PROPERTY(QVariant associateValue MEMBER associateValue)
    Q_PROPERTY(QVector<QPair<QString, QString>> enableConditions MEMBER enableConditions)
    Q_PROPERTY(bool isHighFrequency MEMBER isHighFrequency)

public:
    QString name;
    QVariant type;
    QVariant value;
    QVariant extra;
    QVariant associateValue{QVariant::fromValue(0)};
    QVector<QPair<QString, QString>> enableConditions;
    bool isHighFrequency{false};

    Q_INVOKABLE [[nodiscard]] bool shouldEnable(const QVariant& root) const;
};

Q_DECLARE_METATYPE(MProperty)
