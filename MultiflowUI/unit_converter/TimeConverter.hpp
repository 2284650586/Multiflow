//
// Created by Hatsune Miku on 2023-12-13.
//

#pragma once

#include "unit_converter/AbstractUnitConverter.hpp"

#include <QVector>
#include <QObject>
#include <QString>

class TimeConverter final : public AbstractUnitConverter {
    Q_OBJECT

public:
    explicit TimeConverter(QObject* parent = nullptr);

    Q_INVOKABLE [[nodiscard]]
    QVector<QString> units() const override;

    Q_INVOKABLE [[nodiscard]]
    double convert(double value, const QString& from, const QString& to) const override;
};

Q_DECLARE_METATYPE(TimeConverter)
