//
// Created by miku on 11/13/2023.
//

#include "FormulaService.hpp"
#include "parser/formula_parser.hpp"

#include <MultiflowLibrary/logging/logging.hpp>

void FormulaService::parserAndLoadFormulae() {
    ml::FormulaParser parser{};

    // TODO: hardcoded path
    auto formulae = parser.loadDistribution("D:\\dist.yaml");
    log_info("Loaded {} formula(e).", formulae.size());

    std::ranges::copy(formulae, std::back_inserter(_formulae));
    emit formulaeLoaded();
}

const QVector<ml::Formula>& FormulaService::formulae() const {
    return _formulae;
}
