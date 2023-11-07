//
// Created by miku on 11/6/2023.
//

#include "window_main.hpp"
#include "shared.hpp"

#include <QUrl>

#include <memory>

qml::WindowMain::WindowMain(QObject *parent) {
    // Window shows as the engine create and load.
    gpQmlApplicationEngine = std::make_unique<QQmlApplicationEngine>(
        gpApplication.get());

    std::transform(
        gFormulae.begin(), gFormulae.end(), std::back_inserter(_qmlFormulae),
        [](const auto& formula) { return QmlFormula{formula}; });

    auto* context = gpQmlApplicationEngine->rootContext();
    context->setContextProperty("windowMain", this);

    gpQmlApplicationEngine->load(QUrl("qrc:/qml/main.qml"));
}

QVariantList qml::WindowMain::formulae() const {
    QVariantList ret{};
    for (const QmlFormula& f : _qmlFormulae) {
        ret << QVariant::fromValue(f);
    }
    return ret;
}
