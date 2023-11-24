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

    for (auto it = enableConditions.begin(); it != enableConditions.end(); ++it) {
        const auto value = entity->get(it.key()).value<MProperty>().value.toString();

        if (value != it.value()) {
            return false;
        }
    }
    return true;
}
