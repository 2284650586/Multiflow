#pragma once

#include <QString>
#include <QQuickWindow>

namespace qml {
void initialize(int argc, const char* argv[]);

QQuickWindow* navigate(const QString& route);
}
