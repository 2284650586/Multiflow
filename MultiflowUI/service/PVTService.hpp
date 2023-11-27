//
// Created by Hatsune Miku on 2023-11-26.
//

#pragma once

#include "qml/mixin/SingletonMixin.hpp"
#include "entity/MIndependentVariables.hpp"
#include "entity/MEntity.hpp"
#include "entity/unit/PvtCalculationUnit.hpp"

#include <MultiflowLibrary/formula/formula.hpp>

#include <QObject>
#include <QMap>
#include <fmt/core.h>

class PVTService final : public QObject, public SingletonMixin<PVTService> {
    Q_OBJECT
    friend class SingletonMixin;

    ~PVTService() override;

public:
    void loadData();

    [[nodiscard]] MIndependentVariables* iv() const;

    [[nodiscard]] MEntity* entity() const;

    [[nodiscard]] PvtCalculationUnit* cu() const;

    [[nodiscard]] static QString category();

signals:
    void dataLoaded();

private:
    MIndependentVariables* _iv{};
    MEntity* _entity{};
    PvtCalculationUnit* _cu{};
};
