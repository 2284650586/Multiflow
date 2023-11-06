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
    expression/environment.cpp
    expression/environment.hpp
        formula/formula.cpp
        formula/formula.hpp
    utils/type_utils.cpp
    utils/type_utils.hpp
    expression/multiply.cpp
    expression/multiply.hpp
    expression/divide.cpp
    expression/divide.hpp
        expression/subtract.cpp
        expression/subtract.hpp
        expression/minus.cpp
        expression/minus.hpp
        parser/lisp_parser.cpp
        parser/lisp_parser.hpp
        parser/formula_parser.cpp
        parser/formula_parser.hpp
)

add_definitions(-DMULTIFLOWLIBRARY_LIBRARY)

include_directories(. ${CMAKE_CURRENT_SOURCE_DIR})

# Include yaml-cpp
include(FetchContent)
cmake_policy(SET CMP0135 NEW)
FetchContent_Declare(
        yaml-cpp
        URL https://github.com/jbeder/yaml-cpp/archive/refs/tags/0.8.0.zip
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/yaml-cpp
        DOWNLOAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/yaml-cpp
)
FetchContent_MakeAvailable(yaml-cpp)
find_package(yaml-cpp)

target_link_libraries(MultiflowLibrary PRIVATE Qt6::Core yaml-cpp)
