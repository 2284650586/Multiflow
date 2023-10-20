#ifndef LOGGING_H
#define LOGGING_H

#include "../MultiflowLibrary_global.h"

#include <QString>
#include <QDebug>
#include <QTime>

#include <iostream>
#include <ostream>

namespace logging {

/**
 * @brief 简单的日志系统，跨平台、可做导出库，
 * 供整个项目使用。内部实际调用的qDebug
 *
 * @author z
 */
class ML_PUBLIC Logger {
// Functions
private:
Logger(const QString& level);

public:
/**
 * @brief 日志的初始化。应当在程序启动时调用
 */
static void _initialize();
virtual ~Logger();

// Fields
private:
const QString _level;

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
 * 基本类型，或浮点数，或者QString
 *
 * @return
 */
private:
template<typename T>
const Logger& _log(const T& data) const
{
    qDebug().noquote()
        << QTime::currentTime().toString()
        << "[" << _level << "]"
        << data;
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

// 浮点数特化
DEFINE_LOGGING_SPECIALIZATION(float)
DEFINE_LOGGING_SPECIALIZATION(double)

// QString 特化。以上类型若不专门特化一下，是不能当成库函数来用的
DEFINE_LOGGING_SPECIALIZATION(const QString&);

#undef DEFINE_LOGGING_SPECIALIZATION

};
}

// 定义相关的宏，方便使用
#ifndef LOG_INFO
#define LOG_INFO logging::Logger::info
#define LOG_DEBUG logging::Logger::debug
#define LOG_WARN logging::Logger::warn
#define LOG_ERROR logging::Logger::error
#define LOG_CRITICAL logging::Logger::critical
#endif

#endif // LOGGING_H
