#include "qml/main.hpp"

#include "qml/utils/UIUtils.hpp"
#include "view/window_main.hpp"
#include "shared.hpp"

#include <QQuickStyle>

namespace qml {

void _tryCreateApplicationEngine() {
    if (!gpQmlApplicationEngine) {
        gpQmlApplicationEngine = std::make_unique<QQmlApplicationEngine>(
            gpApplication.get());
    }
}

void _registerSingletons() {
    UIUtils::getInstance()->registerSingleton();
}

void _loadMainWindow() {
    gpWindowMain = std::make_unique<WindowMain>();
}

void _applyVisualStyles() {
    QQuickStyle::setStyle("Material");
}

void start() {
    _tryCreateApplicationEngine();
    _registerSingletons();
    _loadMainWindow();
}

}
