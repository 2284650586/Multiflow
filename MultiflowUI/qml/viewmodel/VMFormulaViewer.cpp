//
// Created by miku on 11/7/2023.
//

#include "VMFormulaViewer.hpp"
#include "shared.hpp"

#include "service/FormulaService.hpp"

namespace qml {

VMFormulaViewer::VMFormulaViewer(QObject*) {
    // Wrap Formula in QmlFormula.
    std::ranges::transform(
        FormulaService::getInstance()->formulae(), std::back_inserter(_qmlFormulae),
        [](const auto& f) { return QmlFormula{f}; });

    gpQmlApplicationEngine->rootContext()->setContextProperty(
        "vmFormulaViewer", this);
}

QVariantList VMFormulaViewer::formulae() const {
    QVariantList ret{};
    for (const QmlFormula& f: _qmlFormulae) {
        ret << QVariant::fromValue(f);
    }
    return ret;
}

}
