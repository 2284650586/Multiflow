cmake_minimum_required(VERSION 3.16)

find_package(Qt6 COMPONENTS Core REQUIRED)

add_library(MultiflowLibrary SHARED
    core/core.cpp
    expression/add.cpp
    expression/expression.cpp
    expression/constant.cpp
    expression/variable.cpp
    math/math.cpp
    logging/logging.cpp
)

add_definitions(-DMULTIFLOWLIBRARY_LIBRARY)

include_directories(. ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(MultiflowLibrary PRIVATE Qt6::Core)
