//
// Created by miku on 11/25/2023.
//

#pragma once

#include "unit_converter/AbstractUnitConverter.hpp"

#include <QVector>
#include <QObject>
#include <QString>

class PressureConverter final : public AbstractUnitConverter {
    Q_OBJECT

public:
    explicit PressureConverter(QObject* parent = nullptr);

    Q_INVOKABLE [[nodiscard]]
    QVector<QString> units() const override;

    Q_INVOKABLE [[nodiscard]]
    double convert(double value, const QString& from, const QString& to) const override;
};

Q_DECLARE_METATYPE(PressureConverter)
