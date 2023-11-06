#pragma once

#include "../MultiflowLibrary_global.hpp"

namespace ml {

/**
 * @brief 整个Multiflow库的初始化。做以下事情:
 *  - 初始化算法库，从配置中加载并实例化算法
 *  - 初始化日志系统
 *  - 连接数据库
 * @author z
 */
ML_PUBLIC void initialize();

}
