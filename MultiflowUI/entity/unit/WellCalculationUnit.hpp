//
// Created by miku on 11/21/2023.
//

#pragma once

#include "entity/unit/generic/CalculationUnit.hpp"

class WellCalculationUnit final : public CalculationUnit {
    Q_OBJECT

    [[nodiscard]]
    QVector<QVector<QVector<ml::Number>>> reservoirPressure() const;

public:
    explicit WellCalculationUnit(QObject* parent = nullptr);

    Q_INVOKABLE [[nodiscard]]
    QVector<QVector<QVector<ml::Number>>> evaluate(const QString& category) const override;
};
