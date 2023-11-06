#ifndef LOGGING_H
#define LOGGING_H

#include "../MultiflowLibrary_global.hpp"

#include <spdlog/spdlog.h>

#define info spdlog::info
#define debug spdlog::debug
#define warn spdlog::warn
#define error spdlog::error
#define critical spdlog::critical
#define trace spdlog::trace

#endif // LOGGING_H
