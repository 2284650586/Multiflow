//
// Created by miku on 11/13/2023.
//

#include "FormulaService.hpp"
#include "parser/formula_parser.hpp"

#include <MultiflowLibrary/logging/logging.hpp>
#include <qml/utils/UIUtils.hpp>

void FormulaService::parserAndLoadFormulae() {
    ml::FormulaParser parser{};

    // TODO: hardcoded path
    try {
        auto formulae = parser.loadDistribution("D:\\dist.yaml");
        log_info("Loaded {} formula(e).", formulae.size());

        std::ranges::copy(formulae, std::back_inserter(_formulae));
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

const QVector<ml::Formula>& FormulaService::formulae() const {
    return _formulae;
}
