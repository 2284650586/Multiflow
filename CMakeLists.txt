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
    set(CMAKE_PREFIX_PATH "改成类似的目录")

else ()
    message(FATAL_ERROR "Unknown developer")

endif ()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup()
set(CMAKE_AUTORCC ON)

add_subdirectory(MultiflowLibrary)
add_subdirectory(MultiflowUI)
