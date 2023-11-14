//
// Created by miku on 11/7/2023.
//

#include "vm_formula_viewer.hpp"
#include "shared.hpp"

#include "service/FormulaService.hpp"

namespace qml {

WindowFormulaViewer::WindowFormulaViewer(QObject* parent) {
    // Wrap Formula in QmlFormula.
    std::ranges::transform(
        FormulaService::getInstance()->formulae(), std::back_inserter(_qmlFormulae),
        [](const auto& f) { return QmlFormula{f}; });

    gpQmlApplicationEngine->rootContext()->setContextProperty(
        "vmFormulaViewer", this);
}

QVariantList WindowFormulaViewer::formulae() const {
    QVariantList ret{};
    for (const QmlFormula& f: _qmlFormulae) {
        ret << QVariant::fromValue(f);
    }
    return ret;
}

}
