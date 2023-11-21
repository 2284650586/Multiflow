//
// Created by miku on 11/20/2023.
//

#pragma once

#include <QVector>
#include <QObject>
#include <QString>

class AbstractUnitConverter : public QObject {
    Q_OBJECT

public:
    explicit AbstractUnitConverter(QObject* parent = nullptr);

    Q_INVOKABLE [[nodiscard]] virtual QVector<QString> units() const = 0;

    Q_INVOKABLE [[nodiscard]] virtual double convert(
        double value,
        const QString& from,
        const QString& to
    ) const = 0;
};
