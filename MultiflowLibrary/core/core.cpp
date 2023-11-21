#include "core.hpp"
#include "logging/logging.hpp"

void ml::initialize() {
    log_init(MultiflowLibrary, level::debug);
    log_debug("Multiflow Core Library Initialized.");
}
