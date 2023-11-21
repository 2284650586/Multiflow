//
// Created by miku on 11/21/2023.
//

#pragma once

#include "entity/unit/generic/CalculationUnit.hpp"

class WellReservoirUnit final : public CalculationUnit {
    Q_OBJECT

public:
    explicit WellReservoirUnit(QObject* parent = nullptr);

    Q_INVOKABLE

    [[nodiscard]] QVector<ml::Number> evaluate() const override;
};
