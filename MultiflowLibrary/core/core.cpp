#include "core.hpp"
#include "logging/logging.hpp"

void ml::initialize() {
    ml::Logger::_initialize();

    LOG_INFO << "Multiflow Core Library Initialized.\n";
}
