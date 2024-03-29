//
// Created by miku on 11/13/2023.
//

#pragma once

#include "qml/mixin/SingletonMixin.hpp"

#include <MultiflowLibrary/formula/formula.hpp>

#include <QObject>
#include <QVector>
#include <QMap>
#include <fmt/core.h>

class FormulaService final : public QObject, public SingletonMixin<FormulaService> {
    Q_OBJECT
    friend class SingletonMixin;

    ~FormulaService() override = default;

public:
    void parseAndLoadFormulae();

    [[nodiscard]]
    QVector<ml::Formula> formulae() const;

    [[nodiscard]]
    ml::Formula formula(const QString& id) const;

signals:
    void formulaeLoaded();

private:
    QMap<QString, ml::Formula> _idToFormula{};
};

class FormulaNotFoundException final : public std::exception {
    std::string _what;

public:
    explicit FormulaNotFoundException(std::string entityName) {
        _what = fmt::format("Formula {} not found.", entityName);
    }
};
