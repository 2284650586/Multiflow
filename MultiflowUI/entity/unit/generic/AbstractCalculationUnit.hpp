//
// Created by miku on 11/21/2023.
//

#pragma once

#include "entity/MIndependentVariables.hpp"
#include "entity/MEntity.hpp"
#include "service/FormulaService.hpp"
#include "helper/MEntityHelper.hpp"

#include <MultiflowLibrary/expression/environment.hpp>

#include <QVector>
#include <QObject>

class AbstractCalculationUnit : public QObject {
    Q_OBJECT

protected:
    MEntity* _entity{};
    MEntityHelper _helper{};
    MIndependentVariables* _independentVariables{};

public:
    explicit AbstractCalculationUnit(QObject* parent = nullptr);

    Q_INVOKABLE void update(const QVariant& entity, const QVariant& independentVariables);

    ~AbstractCalculationUnit() override = default;

    [[nodiscard]] virtual QVector<QVector<QVector<ml::Number>>> evaluate(const QString& category) const = 0;
};
