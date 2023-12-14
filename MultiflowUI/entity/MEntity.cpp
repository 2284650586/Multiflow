//
// Created by miku on 11/20/2023.
//

#include "MEntity.hpp"

#include <logging/logging.hpp>

MEntity::MEntity(QObject* parent): QQmlPropertyMap(parent) {
}

MEntity::MEntity(const MEntity& other): QQmlPropertyMap(other.parent()) {
    copy(this, &other);
}

MEntity& MEntity::operator=(const MEntity& other) {
    copy(this, &other);
    return *this;
}

QVariant MEntity::get(const QString& key) const {
    const auto stdString = key.toStdString();
    return property(stdString.c_str());
}

void MEntity::copy(MEntity* dst, const MEntity* src) {
    for (const auto& key: src->keys()) {
        dst->insert(key, src->value(key));
    }
}

bool MProperty::shouldShow(const QVariant& root) const {
    const auto* propertyMap = root.value<QQmlPropertyMap*>();
    const auto* entity = dynamic_cast<const MEntity*>(propertyMap);

    if (showConditions.isEmpty()) {
        return true;
    }

    const auto predicate = [entity](const auto& pair) {
        const QVariant value = entity->get(pair.first);
        const auto actualValue = value.value<MProperty>().value.toString();

        return actualValue == pair.second;
    };

    if (showIfPolicy.toString().toLower() == "and") {
        return std::ranges::all_of(showConditions, predicate);
    }
    return std::ranges::any_of(showConditions, predicate);
}

bool MProperty::shouldDisable(const MIndependentVariables* iv, const QString& category, int rowIndex) const {
    const auto& rows = iv->get(category);
    if (rowIndex >= rows.size()) {
        log_critical("Row index {} is out of range (size={})", rowIndex, rows.size());
        return false;
    }

    const auto& row = rows[rowIndex];
    return std::ranges::any_of(disableConditions, [&row](const auto& pair) {
        const auto actualValue = row[pair.first].toString();
        return actualValue == pair.second;
    });
}
