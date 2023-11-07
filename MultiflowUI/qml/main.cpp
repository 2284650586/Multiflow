#include "qml/main.hpp"

#include "qml/utils/UIUtils.hpp"
#include "view/window_main.hpp"
#include "shared.hpp"

namespace qml {

void start() {
    UIUtils::getInstance()->registerSingleton();
    gpWindowMain = std::make_unique<WindowMain>();
}

}
