//
// Created by miku on 11/7/2023.
//

#pragma once

#include "qml/model/qml_formula.hpp"

#include <QObject>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQmlContext>

namespace qml {
class WindowFormulaViewer final : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariantList formulae READ formulae NOTIFY onFormulaeUpdated)
    Q_PROPERTY(int selectedFormulaIndex MEMBER _selectedFormulaIndex NOTIFY onSelectFormula)

public:
    explicit WindowFormulaViewer(QObject* parent = nullptr);

    ~WindowFormulaViewer() override = default;

    [[nodiscard]] QVariantList formulae() const;

private:
    QVector<QmlFormula> _qmlFormulae;
    int _selectedFormulaIndex = -1;

signals:
    void onSelectFormula(int index);

    void onFormulaeUpdated();
};
}
