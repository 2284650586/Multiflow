//
// Created by miku on 11/26/2023.
//

#pragma once

#include "qml/mixin/SingletonMixin.hpp"
#include "entity/MIndependentVariables.hpp"

#include <QObject>

class FluidDataService final : public QObject, public SingletonMixin<FluidDataService> {
    Q_OBJECT
    friend class SingletonMixin;

    ~FluidDataService() override = default;

public:
    void loadData();

    static QString categoryBlackOil();

    [[nodiscard]]
    MIndependentVariables* iv() const;

signals:
    void dataLoaded();

private:
    MIndependentVariables* _iv{};
};
