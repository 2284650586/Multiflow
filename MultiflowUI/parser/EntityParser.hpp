//
// Created by miku on 11/20/2023.
//

#pragma once

#include "entity/MEntity.hpp"

#include <yaml-cpp/yaml.h>

#include <QString>
#include <QStack>

struct ParserContext {
    MEntity* entity;
    const QString& propertyName;
    const QString& propertyId;
    const YAML::Node& node;
};

class EntityParser final {
    QMap<QString, QString> _entityFileNameToPath{};
    QMap<QString, MEntity*> _entityNameToEntity{};
    QStack<QString> _pendingEntities{};

public:
    explicit EntityParser() = default;

    ~EntityParser() = default;

    /**
     * @brief 根据目录，递归地加载模型数据
     * @param path structure目录的路径，也就是内含MWell.yaml的那个
     */
    QMap<QString, MEntity*> loadDistribution(const QString& path);

private:
    void _parseDistribution(const YAML::Node& node);

    void _prepareEntityMap(const QString& path);

    void _handleDependencies(const YAML::Node& dependencies);

    void _handleProperties(const QString& entityName, const YAML::Node& properties);

    void _handleReferenceType(const QString& referenceType, const ParserContext& context);

    void _loadEntity(QString entityName);

    void _handleType(const QString& typeName, const ParserContext& context);

    static void _handleBuiltinType(const QString& builtinType, const ParserContext& context);

    static void _handlePrimitiveType(const QString& primitiveType, const ParserContext& context);
};

class ParseException final : public std::exception {
    std::string _what;

public:
    explicit ParseException(std::string what) : _what(std::move(what)) {
    }

    [[nodiscard]] const char* what() const noexcept override {
        return _what.c_str();
    }
};
