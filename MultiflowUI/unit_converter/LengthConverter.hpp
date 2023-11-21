//
// Created by miku on 11/20/2023.
//

#pragma once

#include "unit_converter/AbstractUnitConverter.hpp"

#include <QVector>
#include <QObject>
#include <QString>

// 终究还是自己写出了Converter这种东西，哎呀
class LengthConverter final : public AbstractUnitConverter {
    Q_OBJECT

public:
    explicit LengthConverter(QObject* parent = nullptr);

    Q_INVOKABLE [[nodiscard]]
    QVector<QString> units() const override;

    Q_INVOKABLE [[nodiscard]]
    double convert(double value, const QString& from, const QString& to) const override;
};

Q_DECLARE_METATYPE(LengthConverter)
