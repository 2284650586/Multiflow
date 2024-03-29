//
// Created by Hatsune Miku on 2023-11-26.
//

#pragma once

#include "entity/unit/generic/AbstractCalculationUnit.hpp"

class PvtCalculationUnit final : public AbstractCalculationUnit {
    Q_OBJECT

    int _ivIndex = -1;

    [[nodiscard]] QVector<ml::Number> evaluateOne(
        ml::Number pressure,
        ml::Number temperature,
        const QMap<QString, QVariant>& row
    ) const;

public:
    explicit PvtCalculationUnit(QObject* parent = nullptr);

    Q_INVOKABLE [[nodiscard]]
    QVector<QVector<QVector<ml::Number>>> evaluate(const QString& category) const override;

    Q_INVOKABLE void setIvIndex(int index);

signals:
    void onError(QString error) const;
};
