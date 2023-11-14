#pragma once

#include <QString>

namespace qml {
void initialize(int argc, const char* argv[]);

void navigate(const QString& route);
}
