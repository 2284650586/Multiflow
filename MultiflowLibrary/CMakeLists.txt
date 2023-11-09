cmake_minimum_required(VERSION 3.16)

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
    expression/power.cpp
    expression/power.hpp
    expression/logarithm.cpp
    expression/logarithm.hpp
    expression/logical_and.cpp
    expression/logical_and.hpp
    expression/logical_or.cpp
    expression/logical_or.hpp
    expression/logical_not.cpp
    expression/logical_not.hpp
    expression/condition.cpp
    expression/condition.hpp
    expression/greater_than.cpp
    expression/greater_than.hpp
    expression/lower_than.cpp
    expression/lower_than.hpp
    expression/equal_to.cpp
    expression/equal_to.hpp
)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
    set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
endif()

add_definitions(-DMULTIFLOWLIBRARY_LIBRARY)

include_directories(. ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(MultiflowLibrary PRIVATE yaml-cpp spdlog)
