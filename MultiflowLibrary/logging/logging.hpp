#ifndef LOGGING_H
#define LOGGING_H

#include "../MultiflowLibrary_global.hpp"

#include <iostream>
#include <ostream>

namespace ml {

/**
 * @brief 简单的日志系统，跨平台、可做导出库，
 * 供整个项目使用。内部实际调用的qDebug
 *
 * @author z
 */
class ML_PUBLIC Logger {
// Functions
private:
explicit Logger(std::string level);

public:
/**
 * @brief 日志的初始化。应当在程序启动时调用
 */
static void _initialize();
virtual ~Logger() = default;

// Fields
private:
std::string _level;

public:
/**
 * @brief 全局共享的Logger对象们
 */
static const Logger debug;
static const Logger info;
static const Logger warn;
static const Logger error;
static const Logger critical;

/**
 * @brief 打印日志，会打印时间、日志级别、内容
 *
 * @param data 可以是1,2,4,8,16字节的
 * 基本类型，或浮点数，或者std::string
 *
 * @return
 */
private:
template<typename T>
[[nodiscard]] const Logger& _log(const T& data) const
{
    std::clog << "[" << _level << "] " << data;
    return *this;
}

#define DEFINE_LOGGING_SPECIALIZATION(type) \
    const Logger& operator<<(type data) const { return _log(data); }

public:
// 对1,2,4,8,16字节的基本数据类型的特化
DEFINE_LOGGING_SPECIALIZATION(char)
DEFINE_LOGGING_SPECIALIZATION(short)
DEFINE_LOGGING_SPECIALIZATION(int)
DEFINE_LOGGING_SPECIALIZATION(long)
DEFINE_LOGGING_SPECIALIZATION(long long)
DEFINE_LOGGING_SPECIALIZATION(unsigned long long)

// 浮点数特化
DEFINE_LOGGING_SPECIALIZATION(float)
DEFINE_LOGGING_SPECIALIZATION(double)

DEFINE_LOGGING_SPECIALIZATION(const char*)
DEFINE_LOGGING_SPECIALIZATION(const std::string&)

#undef DEFINE_LOGGING_SPECIALIZATION

};
}

// 定义相关的宏，方便使用
#ifndef LOG_INFO
#define LOG_INFO ml::Logger::info
#define LOG_DEBUG logging::Logger::debug
#define LOG_WARN logging::Logger::warn
#define LOG_ERROR logging::Logger::error
#define LOG_CRITICAL logging::Logger::critical
#endif

#endif // LOGGING_H
