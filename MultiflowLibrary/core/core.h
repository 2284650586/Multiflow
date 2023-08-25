#ifndef CORE_H
#define CORE_H

#include "../MultiflowLibrary_global.h"

namespace ml {

/**
 * @brief 整个Multiflow库的初始化。做以下事情:
 *  - 初始化算法库，从配置中加载并实例化算法
 *  - 初始化日志系统
 *  - 连接数据库
 * @author z
 */
ML_PUBLIC void initialize();

ML_PUBLIC int add(int x, int y);

}

#endif // CORE_H
