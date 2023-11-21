//
// Created by miku on 11/20/2023.
//

#include "MEntity.hpp"

MEntity::MEntity(QObject* parent): QQmlPropertyMap(parent) {
}

MEntity::MEntity(const MEntity& other): QQmlPropertyMap(other.parent()) {
    copy(this, &other);
}

MEntity& MEntity::operator=(const MEntity& other) {
    copy(this, &other);
    return *this;
}

void MEntity::copy(MEntity* dst, const MEntity* src) {
    for (const auto& key : src->keys()) {
        dst->insert(key, src->value(key));
    }
}
