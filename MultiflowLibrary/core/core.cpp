#include "core.hpp"
#include "logging/logging.hpp"

#include <stdexcept>

#include <QDebug>

void ml::initialize() {
    logging::Logger::_initialize();
    LOG_INFO << "Multiflow Core Library Initialized.";
}

int ml::add(int x, int y)
{
    return x + y;
}
