//
// Created by miku on 11/21/2023.
//

#pragma once

#include "entity/MIndependentVariables.hpp"
#include "entity/MEntity.hpp"
#include "service/FormulaService.hpp"

#include <MultiflowLibrary/expression/environment.hpp>

#include <QVector>
#include <QObject>

class CalculationUnit : public QObject {
    Q_OBJECT

protected:
    MEntity* _entity;
    MIndependentVariables* _independentVariables;

public:
    explicit CalculationUnit(QObject* parent = nullptr);

    Q_INVOKABLE void update(const QVariant& entity, const QVariant& independentVariables);

    ~CalculationUnit() override = default;

    [[nodiscard]] virtual QVector<ml::Number> evaluate() const = 0;
};
