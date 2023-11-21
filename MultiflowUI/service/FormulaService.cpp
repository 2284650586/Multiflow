//
// Created by miku on 11/13/2023.
//

#include "FormulaService.hpp"

#include "parser/formula_parser.hpp"
#include "utils/YamlUtils.hpp"

#include <MultiflowLibrary/logging/logging.hpp>
#include <qml/utils/UIUtils.hpp>

void FormulaService::parseAndLoadFormulae() {
    ml::FormulaParser parser{};

    try {
        YAML::Node node{};
        if (!YamlUtils::loadFromQResourcePath(":/resources/model/formulae.yaml", OUT node)) {
            throw std::runtime_error("无法加载公式文件。");
        }
        const auto formulae = parser.parseDistribution(node);
        log_info("Loaded {} formula(e).", formulae.size());

        for (const auto& formula: formulae) {
            _nameToFormula.insert(QString::fromStdString(formula.name()), formula);
        }
        emit formulaeLoaded();
    }
    catch (const ml::MalformedDistException& e) {
        UIUtils::error(QString("加载公式数据遇到错误：%1").arg(e.what()), "好");
    }
    catch (const ml::FunctionNotDefinedException& e) {
        UIUtils::error(QString("分析函数调用关系时遇到错误：%1").arg(e.what()), "好");
    }
    catch (const std::exception& e) {
        UIUtils::error(QString("解析公式文件时遇到错误：%1").arg(e.what()), "好");
    }
}

QVector<ml::Formula> FormulaService::formulae() const {
    return {_nameToFormula.values()};
}

ml::Formula FormulaService::formula(const QString& name) const {
    if (!_nameToFormula.contains(name)) {
        throw FormulaNotFoundException{name.toStdString()};
    }
    return std::move(_nameToFormula[name]);
}
