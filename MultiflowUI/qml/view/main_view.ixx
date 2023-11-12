//
// Created by miku on 11/6/2023.
//

module;

#include "main_view.moc"
#include <QObject>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQmlContext>

#include "shared.hpp"

#include <QUrl>

export module main_view;

import formula_viewer;

export namespace qml {

class WindowMain : public QObject {
Q_OBJECT

public:
    explicit WindowMain(QObject* parent = nullptr) {
        gpQmlApplicationEngine->rootContext()->setContextProperty(
            "vmWindowMain", this);

        // Window shows as the engine loads.
        gpQmlApplicationEngine->load(QUrl("qrc:/qml/main.qml"));
    }

    ~WindowMain() override = default;

public slots:
    void onFormulaViewerButtonClicked() {
        gpWindowFormulaViewer = std::make_unique<WindowFormulaViewer>();
    }
};

}
