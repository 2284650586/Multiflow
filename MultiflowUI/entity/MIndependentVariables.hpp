//
// Created by miku on 11/21/2023.
//

#pragma once

#include <QObject>
#include <QVector>
#include <QMap>
#include <QVariant>

class MIndependentVariables final : public QObject {
    Q_OBJECT

    // v[category][index][key]
    QMap<QString, QVector<QMap<QString, QVariant>>> _variables;

public:
    explicit MIndependentVariables(QObject* parent = nullptr);

    Q_INVOKABLE [[nodiscard]] size_t size(const QString& category) const;

    Q_INVOKABLE void createEmpty(const QString& category);

    Q_INVOKABLE void remove(const QString& category, int index);

    Q_INVOKABLE void set(const QString& category, int index, const QString& key, const QVariant& value);

    Q_INVOKABLE [[nodiscard]] QVariant get(const QString& category, int index, const QString& key) const;

    Q_INVOKABLE [[nodiscard]] QVector<QMap<QString, QVariant>> get(const QString& category) const;

signals:
    void sizeChanged(QString category);

    void propertyChanged(QString category);
};

Q_DECLARE_METATYPE(MIndependentVariables)
