cmake_minimum_required(VERSION 3.16)

# 设置项目名和版本号
project(
    Multiflow
    VERSION 1.0.0
    LANGUAGES CXX
)

# 设置C++标准为C++20
set(CMAKE_CXX_STANDARD 20)

# 导入Qt本体
find_package(Qt6 REQUIRED COMPONENTS Core)

# 启用Qt6对CMake的支持，并启用自动UIC
# 自动UIC是指把.ui文件分析成.h和.cpp文件
# 并且自动添加到项目中
qt_standard_project_setup()

# 启用自动RCC，这样项目能够识别.qrc文件
set(CMAKE_AUTORCC ON)

# 编译Multiflow核心库
add_subdirectory(MultiflowLibrary)

# 编译MultiflowUI
add_subdirectory(MultiflowUI)
