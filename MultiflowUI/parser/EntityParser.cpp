//
// Created by miku on 11/20/2023.
//

#include "EntityParser.hpp"
#include "utils/YamlUtils.hpp"
#include "unit_converter/LengthConverter.hpp"
#include "unit_converter/PressureConverter.hpp"
#include "unit_converter/TemperatureConverter.hpp"
#include "unit_converter/FluidUnitConverter.hpp"
#include "unit_converter/GasRatioConverter.hpp"
#include "unit_converter/RatioFractionConverter.hpp"

#include <QDir>
#include <QVariant>
#include <logging/logging.hpp>

static const auto BuiltinTypeToConverterFactory = QMap<QString, std::function<AbstractUnitConverter*()>>{
    {"Builtin.Length", [] { return new LengthConverter{}; }},
    {"Builtin.Pressure", [] { return new PressureConverter{}; }},
    {"Builtin.Temperature", [] { return new TemperatureConverter{}; }},
    {"Builtin.FluidUnit", [] { return new FluidUnitConverter{}; }},
    {"Builtin.GasRatio", [] { return new GasRatioConverter{}; }},
    {"Builtin.RatioFraction", [] { return new RatioFractionConverter{}; }},
};

static const auto PrimitiveTypeToDefaultValue = QMap<QString, QVariant>{
    {"number", QVariant::fromValue(static_cast<double>(0))},
    {"string", QVariant::fromValue(QString{})},
};

static QString qFromNode(const YAML::Node& node) {
    return QString::fromStdString(node.as<std::string>(""));
}

// NOLINTNEXTLINE(misc-no-recursion)
QMap<QString, MEntity*> EntityParser::loadDistribution(const QString& path) {
    _entityFileNameToPath.clear();
    _entityNameToEntity.clear();
    _pendingEntities.clear();

    _prepareEntityMap(path);

    for (const auto& keys = _entityFileNameToPath.keys();
         const auto& entityName: keys) {
        log_info("Loading entity: {}", entityName.toStdString());
        _loadEntity(entityName);
    }

    return _entityNameToEntity;
}

// NOLINTNEXTLINE(misc-no-recursion)
void EntityParser::_prepareEntityMap(const QString& path) {
    const QDir root{path};

    for (const auto files = root.entryList(QDir::Files);
         const auto& file: files) {
        if (!file.endsWith(".yaml")) {
            log_info("Skipping non-yaml file: {}", file.toStdString());
            continue;
        }
        _entityFileNameToPath[file] = root.filePath(file);
    }

    constexpr auto 这也太形象了吧 = QDir::NoDotAndDotDot;
    for (auto subDirectories = root.entryList(QDir::Dirs | 这也太形象了吧);
         const auto& subDirectory: subDirectories) {
        QString fullPath = root.filePath(subDirectory);
        loadDistribution(fullPath);
    }
}

// NOLINTNEXTLINE(misc-no-recursion)
void EntityParser::_loadEntity(QString entityName) {
    if (!entityName.endsWith(".yaml")) {
        entityName += ".yaml";
    }
    YAML::Node node{};
    if (const QString& path = _entityFileNameToPath[entityName];
        !YamlUtils::loadFromQResourcePath(path, OUT node)) {
        throw ParseException{
            fmt::format("Failed to load entity file: {}", entityName.toStdString())
        };
    }
    _parseDistribution(node);
}

// NOLINTNEXTLINE(misc-no-recursion)
void EntityParser::_parseDistribution(const YAML::Node& node) {
    if (!node["multiflow-dist"].IsDefined()) {
        throw ParseException{"Not a multiflow distribution file."};
    }

    const auto& name = node["name"];
    if (!name.IsDefined()) {
        throw ParseException{"No name defined."};
    }
    if (const auto& dependencies = node["import"];
        dependencies.IsDefined()) {
        _handleDependencies(dependencies);
    }

    const QString entityName = qFromNode(name);

    const auto& properties = node["properties"];
    if (!properties.IsDefined()) {
        throw ParseException{"No properties defined."};
    }
    _handleProperties(entityName, properties);
}

// NOLINTNEXTLINE(misc-no-recursion)
void EntityParser::_handleDependencies(const YAML::Node& dependencies) {
    for (const auto& dependency: dependencies) {
        QString depName = qFromNode(dependency);
        if (_entityNameToEntity.contains(depName)) {
            // Already loaded.
            continue;
        }
        if (_pendingEntities.contains(depName)) {
            // Dependency loop.
            throw ParseException{
                fmt::format("Dependency loop detected: {}", depName.toStdString())
            };
        }
        _pendingEntities.push(depName);
        _loadEntity(depName);
        _pendingEntities.pop();
    }
}

void EntityParser::_handleProperties(const QString& entityName, const YAML::Node& properties) {
    auto* entity = new MEntity{};
    for (const auto& property: properties) {
        const auto id = property["id"];
        const auto name = property["name"];
        const auto type = property["type"];
        const auto example = property["example"];
        const auto preferredUnit = property["preferred-unit"];
        const bool isHighFrequency = property["independent"].IsDefined() && property["independent"].as<bool>();

        if (!id.IsDefined() || !name.IsDefined() || !type.IsDefined()) {
            throw ParseException{
                fmt::format("Malformed property of entity {}.", entityName.toStdString())
            };
        }

        const auto enableConditions = property["enable-if"];
        QVector<QPair<QString, QString>> conditions{};
        for (const auto& condition: enableConditions) {
            const auto enumId = condition["enum-id"];
            const auto value = condition["value"];
            if (!enumId.IsDefined() || !value.IsDefined()) {
                throw ParseException{
                    fmt::format("Malformed enable-if of entity {}.", entityName.toStdString())
                };
            }
            conditions.emplace_back(qFromNode(enumId), qFromNode(value));
        }

        _handleType(
            qFromNode(type), {
                .entity = entity,
                .propertyName = qFromNode(name),
                .propertyId = qFromNode(id),
                .exampleValue = qFromNode(example),
                .preferredUnit = qFromNode(preferredUnit),
                .node = property,
                .isHighFrequency = isHighFrequency,
                .enableConditions = conditions,
            });
    }

    _entityNameToEntity.insert(entityName, entity);
}

void EntityParser::_handleType(const QString& typeName, const ParserContext& context) {
    if (typeName.isEmpty()) {
        throw ParseException{"Empty type name."};
    }

    if (typeName.startsWith("Builtin.")) {
        // Builtin type.
        _handleBuiltinType(typeName, context);
    }
    else if (typeName[0].isLower()) {
        // 小写字母开头的是基础类型
        _handlePrimitiveType(typeName, context);
    }
    else {
        _handleReferenceType(typeName, context);
    }
}

void EntityParser::_handleBuiltinType(const QString& builtinType, const ParserContext& context) {
    if (!BuiltinTypeToConverterFactory.contains(builtinType)) {
        throw ParseException{
            fmt::format("Unknown builtin type: {}", builtinType.toStdString())
        };
    }
    context.entity->insert(
        context.propertyId,
        QVariant::fromValue(MProperty{
            .name = context.propertyName,
            .type = builtinType,
            .value = QVariant::fromValue(context.exampleValue.toDouble()),
            .extra = QVariant::fromValue(BuiltinTypeToConverterFactory[builtinType]()),
            .example = QVariant::fromValue(context.exampleValue),
            .preferredUnit = QVariant::fromValue(context.preferredUnit),
            .isHighFrequency = context.isHighFrequency,
            .enableConditions = context.enableConditions,
        })
    );
}

void EntityParser::_handleReferenceType(const QString& referenceType, const ParserContext& context) {
    if (!_entityNameToEntity.contains(referenceType)) {
        throw ParseException{
            fmt::format("Unknown reference type: {}", referenceType.toStdString())
        };
    }
    const auto* entityValue = _entityNameToEntity[referenceType];
    context.entity->insert(
        context.propertyId, QVariant::fromValue(MProperty{
            .name = context.propertyName,
            .type = QVariant::fromValue(referenceType),
            .value = QVariant::fromValue(new MEntity{*entityValue}),
            .extra = QVariant{},
            .example = QVariant::fromValue(context.exampleValue),
            .preferredUnit = QVariant::fromValue(context.preferredUnit),
            .isHighFrequency = context.isHighFrequency,
            .enableConditions = context.enableConditions,
        })
    );
}

void EntityParser::_handlePrimitiveType(const QString& primitiveType, const ParserContext& context) {
    if (primitiveType == "enum") {
        const auto& enumField = context.node["enum"];
        if (!enumField.IsDefined()) {
            throw ParseException(
                fmt::format("没有给枚举类型定义数据: {}", context.propertyName.toStdString()));
        }
        const QString enums = qFromNode(enumField);
        const auto enumList = enums.split(", ");

        context.entity->insert(
            context.propertyId, QVariant::fromValue(MProperty{
                .name = context.propertyName,
                .type = QVariant::fromValue(primitiveType),
                .value = QVariant::fromValue(enumList.first()),
                .extra = QVariant::fromValue(enums),
                .example = QVariant::fromValue(context.exampleValue),
                .preferredUnit = QVariant::fromValue(context.preferredUnit),
                .isHighFrequency = context.isHighFrequency,
                .enableConditions = context.enableConditions,
            }));
        return;
    }

    if (!PrimitiveTypeToDefaultValue.contains(primitiveType)) {
        throw ParseException{
            fmt::format("Unknown primitive type: {}", primitiveType.toStdString())
        };
    }
    context.entity->insert(
        context.propertyId, QVariant::fromValue(MProperty{
            .name = context.propertyName,
            .type = QVariant::fromValue(primitiveType),
            .value = context.exampleValue.isEmpty()
                         ? PrimitiveTypeToDefaultValue[primitiveType]
                         : QVariant::fromValue(context.exampleValue.toDouble()),
            .extra = QVariant{},
            .example = QVariant::fromValue(context.exampleValue),
            .preferredUnit = QVariant::fromValue(context.preferredUnit),
            .isHighFrequency = context.isHighFrequency,
            .enableConditions = context.enableConditions,
        }));
}
