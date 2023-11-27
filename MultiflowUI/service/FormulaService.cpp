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
            _idToFormula.insert(QString::fromStdString(formula.id()), formula);
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
    return {_idToFormula.values()};
}

ml::Formula FormulaService::formula(const QString& id) const {
    if (!_idToFormula.contains(id)) {
        throw FormulaNotFoundException{id.toStdString()};
    }
    return _idToFormula[id];
}
