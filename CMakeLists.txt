cmake_minimum_required(VERSION 3.27)

project(
    Multiflow
    VERSION 1.0.0
    LANGUAGES CXX
)

if ("$ENV{QT_DEV_ENV}" STREQUAL "Z")
    message(STATUS "Developer: z")
    if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        set(CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/qt/6.6.0")
        set(CMAKE_OSX_ARCHITECTURES "arm64")
    else ()
        set(CMAKE_PREFIX_PATH "D:/Qt/6.5.2/msvc2019_64")
    endif ()

elseif ("$ENV{QT_DEV_ENV}" STREQUAL "LXT")
    message(STATUS "Developer: lxt")
    set(CMAKE_PREFIX_PATH "C:/Qt/6.5.3/msvc2019_64")
    set(ENV{http_proxy} "http://127.0.0.1:7890")
    set(ENV{https_proxy} "http://127.0.0.1:7890")

else ()
    message(FATAL_ERROR "Unknown developer")

endif ()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
cmake_policy(SET CMP0135 NEW)

include_directories(MultiflowLibrary MultiflowUI)

# Include yaml-cpp
FetchContent_Declare(
    yaml-cpp
    URL https://github.com/jbeder/yaml-cpp/archive/refs/tags/0.8.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP 1
)
FetchContent_MakeAvailable(yaml-cpp)
find_package(yaml-cpp)
include_directories(${yaml-cpp_SOURCE_DIR}/include)

# Include spdlog
FetchContent_Declare(
    spdlog
    URL https://github.com/gabime/spdlog/archive/refs/tags/v1.12.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP 1
)
FetchContent_MakeAvailable(spdlog)
include_directories(${spdlog_SOURCE_DIR}/include)

# Include fmt
FetchContent_Declare(
    fmt
    URL https://github.com/fmtlib/fmt/releases/download/10.1.1/fmt-10.1.1.zip
    DOWNLOAD_EXTRACT_TIMESTAMP 1
)
FetchContent_MakeAvailable(fmt)
include_directories(${fmt_SOURCE_DIR}/include)

if (NOT (CMAKE_SYSTEM_NAME STREQUAL "Darwin"))
    # Place executables and libraries in the same directory
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif ()

add_subdirectory(MultiflowLibrary)

# Include FluentUI
# 这个库写的不行，一大堆警告，屏蔽一下
set(FRAMELESSHELPER_NO_SUMMARY OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "Initial CXX Flags" FORCE)
add_compile_options(-w)
set(FLUENTUI_BUILD_EXAMPLES OFF)
set(FLUENTUI_BUILD_FRAMELESSHELPER OFF)
set(FLUENTUI_BUILD_STATIC_LIB ON)
add_subdirectory(FluentUIExt)

# 解除对警告的屏蔽
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "Restored CXX Flags" FORCE)

add_subdirectory(MultiflowUI)
