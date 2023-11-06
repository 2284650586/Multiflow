cmake_minimum_required(VERSION 3.16)

project(
    Multiflow
    VERSION 1.0.0
    LANGUAGES CXX
)

if ( "$ENV{QT_DEV_ENV}" STREQUAL "Z" )
    message(STATUS "Developer: z")
    set(CMAKE_PREFIX_PATH "D:/Qt/6.5.2/msvc2019_64")

elseif ( "$ENV{QT_DEV_ENV}" STREQUAL "LXT" )
    message(STATUS "Developer: lxt")
    set(CMAKE_PREFIX_PATH "C:/Qt/6.5.3/msvc2019_64")

else ()
    message(FATAL_ERROR "Unknown developer")

endif ()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup()
set(CMAKE_AUTORCC ON)

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

add_subdirectory(MultiflowLibrary)
add_subdirectory(MultiflowUI)
