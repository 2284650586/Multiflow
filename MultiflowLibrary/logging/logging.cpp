#include "logging.hpp"

namespace ml {

const Logger Logger::debug = Logger("DEBUG");
const Logger Logger::info = Logger("INFO");
const Logger Logger::warn = Logger("WARN");
const Logger Logger::error = Logger("ERROR");
const Logger Logger::critical = Logger("CRITICAL");

void Logger::_initialize()
{
    Logger::info << "Logger initialized.";
}

Logger::Logger(std::string level): _level(std::move(level))
{

}

}
