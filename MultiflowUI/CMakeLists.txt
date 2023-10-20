cmake_minimum_required(VERSION 3.16)

find_package(
    Qt6 6.5
    COMPONENTS Core Gui Charts Widgets
    Quick QuickWidgets
    REQUIRED
)
aux_source_directory(entity ENTITY)
aux_source_directory(entity/component/flowline ENTITY_FLOWLINE)
aux_source_directory(entity/component/well ENTITY_WELL)
aux_source_directory(parUI PARUI)
aux_source_directory(TView TVIEW)
aux_source_directory(TWidget TWIDGET)
aux_source_directory(util UTIL)
aux_source_directory(util/delegate UTIL_DELEGATE)
aux_source_directory(util/validator UTIL_VALIDATOR)
aux_source_directory(utility UTILITY)

set(QML_SRC
    qml/main.qml
)

set(SOURCE_FILES
    ${ENTITY}
    ${ENTITY_FLOWLINE}
    ${ENTITY_WELL}
    ${PARUI}
    ${TVIEW}
    ${TWIDGET}
    ${UTIL}
    ${UTIL_DELEGATE}
    ${UTIL_VALIDATOR}
    ${UTILITY}
    main.cpp
    mainwindow.cpp
    shared.cpp
    resources.qrc
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR} 
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
    ../
)

qt_add_executable(
    MultiflowUI
    ${SOURCE_FILES}
)

qt_add_qml_module(
    MultiflowUI
    URI qml.main
    RESOURCE_PREFIX qml
    QML_FILES
        ${QML_SRC}
    RESOURCES
        resources.qrc
)

target_link_libraries(
    MultiflowUI
    PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Charts
    Qt6::Widgets
    Qt6::Widgets
    Qt6::Quick
    Qt6::QuickWidgets
    MultiflowLibrary
)