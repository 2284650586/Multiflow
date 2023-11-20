#include "qml/main.hpp"
#include "qml/utils/UIUtils.hpp"
#include "model/QmlEnvironment.hpp"
#include "viewmodel/VMFormulaViewer.hpp"
#include "helper/SettingsHelper.hpp"
#include "shared.hpp"

#include <QQuickStyle>
#include <QtQml/qqmlextensionplugin.h>

Q_IMPORT_QML_PLUGIN(FluentUIPlugin)
#include <FluentUI/src/FluApp.h>
#include <FluentUI/src/FluentUI.h>

namespace qml {
static bool _didInitialized = false;

void _tryCreateApplicationEngine() {
    if (!gpQmlApplicationEngine) {
        gpQmlApplicationEngine = new QQmlApplicationEngine{gpApplication.get()};
        FluentUI::getInstance()->registerTypes(gpQmlApplicationEngine);
    }
}

void _registerSingletons() {
    const auto& engine = *gpQmlApplicationEngine;
    UIUtils::getInstance()->registerSingleton(engine);
    SettingsHelper::getInstance()->registerSingleton(engine);
    QmlEnvironment::createInstance()->registerObjectType();

    qmlRegisterSingletonType(
        {"qrc:/qml/components/singleton/FluColors.qml"}, "Multiflow.UI", 1, 0, "FluColors");
}

void _applyVisualStyles() {
    QQuickStyle::setStyle("Basic");
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(
        Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

    if (SettingsHelper::getInstance()->getRender() == "software") {
        QQuickWindow::setGraphicsApi(QSGRendererInterface::Software);
    }
}

void _initializeViewModels() {
    gpQmlVMFormulaViewer = std::make_unique<VMFormulaViewer>();
}

void initialize(int, const char* argv[]) {
    QGuiApplication::setOrganizationName("CNU");
    QGuiApplication::setApplicationName("Multiflow");
    SettingsHelper::getInstance()->init(argv);
    SettingsHelper::getInstance()->setRender("hardware");

    _tryCreateApplicationEngine();
    _applyVisualStyles();
    _registerSingletons();
    _initializeViewModels();
}

void navigate(const QString& route) {
    if (!_didInitialized) {
        gpQmlApplicationEngine->load(QUrl("qrc:/qml/main.qml"));
        _didInitialized = true;
    }
    FluApp::getInstance()->navigate(route);
}
}
