#pragma once

#include "MultiflowLibrary_global.hpp"

// #define SPDLOG_WCHAR_TO_UTF8_SUPPORT
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#define SPDLOG_FMT_EXTERNAL
#define SPDLOG_HEADER_ONLY
#define FMT_HEADER_ONLY
#undef SPDLOG_COMPILED_LIB

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#define log_init(name, level) spdlog::set_default_logger(spdlog::stdout_color_mt(#name)); spdlog::set_level(spdlog::level)
#define log_info spdlog::info
#define log_debug spdlog::debug
#define log_warn spdlog::warn
#define log_error spdlog::error
#define log_critical spdlog::critical
#define log_trace spdlog::trace
