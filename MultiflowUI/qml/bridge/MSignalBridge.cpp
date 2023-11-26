#include "MSignalBridge.hpp"

#include <QMetaMethod>

MSignalBridge::MSignalBridge(QObject* parent): QObject(parent) {

}

bool MSignalBridge::isConnected(const QMetaMethod& signal) const {
    return isSignalConnected(signal);
}
