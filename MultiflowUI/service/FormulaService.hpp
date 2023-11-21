//
// Created by miku on 11/13/2023.
//

#pragma once

#include "qml/mixin/SingletonMixin.hpp"

#include <MultiflowLibrary/formula/formula.hpp>

#include <QObject>
#include <QVector>

class FormulaService final : public QObject, public SingletonMixin<FormulaService> {
    Q_OBJECT
    friend class SingletonMixin;
    ~FormulaService() override = default;

public:
    void parseAndLoadFormulae();

    [[nodiscard]]
    const QVector<ml::Formula>& formulae() const;

signals:
    void formulaeLoaded();

private:
    QVector<ml::Formula> _formulae;
};
