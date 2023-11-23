//
// Created by miku on 11/20/2023.
//

#pragma once

#include "qml/mixin/SingletonMixin.hpp"
#include "entity/MEntity.hpp"

#include <QObject>
#include <QMap>
#include <QVector>
#include <fmt/core.h>

class EntityService final : public QObject, public SingletonMixin<EntityService> {
    Q_OBJECT
    friend class SingletonMixin;

    ~EntityService() override = default;

public:
    void parserAndLoadEntities();

    MEntity* createEntity(const QString& name, QObject* parent = nullptr);

signals:
    void entitiesLoaded();

private:
    QMap<QString, MEntity*> _entityNameToEntity{};
};

class EntityNotFoundException final : public std::exception {
    std::string _what;

public:
    explicit EntityNotFoundException(std::string entityName) {
        _what = fmt::format("Entity {} not found.", entityName);
    }
};
