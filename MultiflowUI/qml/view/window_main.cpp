//
// Created by miku on 11/6/2023.
//

#include "window_main.hpp"
#include "window_formula_viewer.hpp"
#include "shared.hpp"

#include <QUrl>

namespace qml {

WindowMain::WindowMain(QObject* parent) {
    gpQmlApplicationEngine->rootContext()->setContextProperty(
        "vmWindowMain", this);

    // Window shows as the engine loads.
    gpQmlApplicationEngine->load(QUrl("qrc:/qml/main.qml"));
}

void WindowMain::onFormulaViewerButtonClicked() {
    gpQmlWindowFormulaViewer = std::make_unique<WindowFormulaViewer>();
}

}
