//
// Created by miku on 11/6/2023.
//

#pragma once

#include "qml/model/qml_formula.hpp"

#include <QObject>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQmlContext>

namespace qml {

class WindowMain: public QObject {
Q_OBJECT
Q_PROPERTY(QVariantList formulae READ formulae)

public:
    explicit WindowMain(QObject *parent = nullptr);
    ~WindowMain() override = default;

    QVariantList formulae() const;

private:
    QVector<QmlFormula> _qmlFormulae;
};

}
