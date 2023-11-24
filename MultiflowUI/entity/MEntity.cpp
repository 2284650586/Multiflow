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

bool MProperty::shouldEnable(const QVariant& root) const {
    const auto* propertyMap = root.value<QQmlPropertyMap*>();
    const auto* entity = dynamic_cast<const MEntity*>(propertyMap);

    if (enableConditions.isEmpty()) {
        return true;
    }

    return std::ranges::any_of(enableConditions, [entity](const auto& pair) {
        const QVariant value = entity->get(pair.first);
        const auto actualValue = value.value<MProperty>().value.toString();

        return actualValue == pair.second;
    });
}
