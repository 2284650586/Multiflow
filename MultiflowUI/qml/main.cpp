#include "qml/main.hpp"

#include "qml/utils/UIUtils.hpp"
#include "qml/model/qml_environment.hpp"
#include "viewmodel\vm_formula_viewer.hpp"
#include "helper/settings_helper.hpp"
#include "shared.hpp"

#include <QQuickStyle>
#include <QQuickWindow>

#include <QtQml/qqmlextensionplugin.h>

Q_IMPORT_QML_PLUGIN(FluentUIPlugin)
#include <FluentUI/src/FluApp.h>

namespace qml {

static bool _didInitialized = false;

void _tryCreateApplicationEngine() {
    if (!gpQmlApplicationEngine) {
        gpQmlApplicationEngine = new QQmlApplicationEngine(gpApplication.get());
    }
}

void _registerSingletons() {
    const auto& engine = *gpQmlApplicationEngine;
    UIUtils::getInstance()->registerSingleton(engine);
    SettingsHelper::getInstance()->registerSingleton(engine);
    QmlEnvironment::createInstance()->registerObjectType();

    qmlRegisterSingletonType(
        QUrl("qrc:/qml/components/singleton/FormulaItemsSingleton.qml"),
        "qml.main", 1, 0, "FormulaItemsSingleton");
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
    gpQmlWindowFormulaViewer = std::make_unique<WindowFormulaViewer>();
}

void initialize(int argc, const char* argv[]) {
    QGuiApplication::setOrganizationName("CNU");
    QGuiApplication::setApplicationName("Multiflow");
    SettingsHelper::getInstance()->init(argv);
    SettingsHelper::getInstance()->setRender("hardware");

    QSurfaceFormat format;
    format.setVersion(3, 2);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

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
