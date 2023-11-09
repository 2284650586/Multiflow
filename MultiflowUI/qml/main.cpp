#include "qml/main.hpp"

#include "qml/utils/UIUtils.hpp"
#include "qml/model/qml_environment.hpp"
#include "view/window_main.hpp"
#include "helper/settings_helper.hpp"
#include "shared.hpp"

#include <QQuickStyle>
#include <QQuickWindow>

namespace qml {

void _tryCreateApplicationEngine() {
    if (!gpQmlApplicationEngine) {
        gpQmlApplicationEngine = new QQmlApplicationEngine(gpApplication);
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

void _loadMainWindow() {
    gpWindowMain = std::make_unique<WindowMain>();
}

void _applyVisualStyles() {
    QQuickStyle::setStyle("Basic");
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(
        Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

    if (SettingsHelper::getInstance()->getRender() == "software") {
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
        QQuickWindow::setGraphicsApi(QSGRendererInterface::Software);
#elif (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
        QQuickWindow::setSceneGraphBackend(QSGRendererInterface::Software);
#endif
    }
}

void start(int argc, char* argv[]) {
    QGuiApplication::setOrganizationName("CNU");
    QGuiApplication::setApplicationName("Multiflow");
    SettingsHelper::getInstance()->init(argv);
    SettingsHelper::getInstance()->setRender("hardware");

    _tryCreateApplicationEngine();
    _applyVisualStyles();
    _registerSingletons();
    _loadMainWindow();
}

}
