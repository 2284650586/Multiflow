//
// Created by miku on 11/20/2023.
//

#include "EntityService.hpp"
#include "parser/EntityParser.hpp"
#include "qml/utils/UIUtils.hpp"

#include <MultiflowLibrary/logging/logging.hpp>

void EntityService::parserAndLoadEntities() {
    EntityParser parser{};
    try {
        _entityNameToEntity = parser.loadDistribution(
            ":/resources/model/structure");
        log_info("Loaded {} entity(ies).", _entityNameToEntity.size());
        emit entitiesLoaded();
    }
    catch (const ParseException& e) {
        UIUtils::error(QString("加载实体数据时遇到错误：%1").arg(e.what()), "好");
    }
    catch (const std::exception& e) {
        UIUtils::error(QString("加载实体数据时遇到错误：%1").arg(e.what()), "好");
    }
}

MEntity* EntityService::createEntity(const QString& name, QObject* parent) {
    if (!_entityNameToEntity.contains(name)) {
        throw EntityNotFoundException{name.toStdString()};
    }
    const auto* prototype = _entityNameToEntity[name];
    auto* ret = new MEntity{*prototype};
    ret->setParent(parent);
    return ret;
}
