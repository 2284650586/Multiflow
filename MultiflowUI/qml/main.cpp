#include "main.hpp"

#include "qml/utils/UIUtils.hpp"

namespace qml {

void registerQmlComponents() {
    UIUtils::getInstance()->registerSingleton();
}

}
