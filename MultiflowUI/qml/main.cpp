#include "main.hpp"

#include "qml/utils/UIUtils.hpp"

namespace qml {

void registerQmlComponents() {
    qmlRegisterType<UIUtils>("Multiflow.UI", 1, 0, "UIUtils");
}

}
