//
// Created by miku on 11/7/2023.
//

#include "window_formula_viewer.hpp"
#include "shared.hpp"

#include <QUrl>

namespace qml {

qml::WindowFormulaViewer::WindowFormulaViewer(QObject* parent) {
    // Wrap Formula in QmlFormula.
    std::transform(
        gFormulae.begin(), gFormulae.end(), std::back_inserter(_qmlFormulae),
        [](const auto& formula) { return QmlFormula{formula}; });

    gpQmlApplicationEngine->rootContext()->setContextProperty(
        "vmFormulaViewer", this);

    // Window shows as the engine loads.
    gpQmlApplicationEngine->load(QUrl("qrc:/qml/components/window/FormulaViewer.qml"));
}

QVariantList qml::WindowFormulaViewer::formulae() const {
    QVariantList ret{};
    for (const QmlFormula& f: _qmlFormulae) {
        ret << QVariant::fromValue(f);
    }
    return ret;
}

}
