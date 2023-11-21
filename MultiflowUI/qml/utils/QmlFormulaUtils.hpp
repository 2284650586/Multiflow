//
// Created by miku on 11/21/2023.
//

#pragma once

#include <QString>
#include <QObject>

#include "qml/mixin/SingletonMixin.hpp"
#include "qml/interface/IQmlSingleton.hpp"
#include "qml/model/QmlFormula.hpp"

class QmlFormulaUtils final : public QObject, public SingletonMixin<QmlFormulaUtils>,
                              public IQmlSingleton<QmlFormulaUtils> {
    Q_OBJECT

    friend class SingletonMixin;

public:
    /**
     * @return true if positive button is clicked, false otherwise
     */
    Q_INVOKABLE [[maybe_unused]] static QmlFormula formula(const QString& name);

private:
    explicit QmlFormulaUtils(QObject* parent = nullptr);
};
