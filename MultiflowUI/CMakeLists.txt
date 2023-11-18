cmake_minimum_required(VERSION 3.28)

find_package(
    Qt6 6.5
    COMPONENTS Core Gui Charts Widgets
    Quick QuickWidgets QuickControls2
    REQUIRED
)

qt_standard_project_setup()
set(CMAKE_AUTORCC ON)

aux_source_directory(entity ENTITY)
aux_source_directory(entity/component/flowline ENTITY_FLOWLINE)
aux_source_directory(entity/component/well ENTITY_WELL)
aux_source_directory(editor EDITOR)
aux_source_directory(graphics_view GRAPHICS_VIEW)
aux_source_directory(graphics_view/widget TWIDGET)
aux_source_directory(util UTIL)
aux_source_directory(util/delegate UTIL_DELEGATE)
aux_source_directory(util/validator UTIL_VALIDATOR)
aux_source_directory(utility UTILITY)
aux_source_directory(widget WIDGET)
aux_source_directory(service SERVICE)
file(GLOB_RECURSE HEADERS
    *.h
    *.hpp
)

set(QML_SRC
    qml/main.qml
)

set(SOURCE_FILES
    ${ENTITY}
    ${ENTITY_FLOWLINE}
    ${ENTITY_WELL}
    ${EDITOR}
    ${GRAPHICS_VIEW}
    ${TWIDGET}
    ${UTIL}
    ${UTIL_DELEGATE}
    ${UTIL_VALIDATOR}
    ${UTILITY}
    ${WIDGET}
    ${SERVICE}
    ${HEADERS}
    main.cpp
    widget/MainWindow.cpp
    widget/SplashDialog.cpp
    shared.cpp
    resources.qrc
    qml/main.cpp
    qml/utils/UIUtils.cpp
    qml/model/QmlFormula.cpp
    qml/model/QmlFormula.hpp
    qml/model/QmlExpression.cpp
    qml/model/QmlExpression.hpp
    qml/viewmodel/VMFormulaViewer.cpp
    qml/viewmodel/VMFormulaViewer.hpp
    helper/SettingsHelper.cpp
    helper/SettingsHelper.hpp
    qml/model/QmlEnvironment.cpp
    qml/model/QmlEnvironment.hpp
    qml/model/QmlResult.cpp
    qml/model/QmlResult.hpp
    service/FormulaService.cpp
    service/FormulaService.hpp
    graphics_view/MAbstractItem.cpp
    graphics_view/MAbstractItem.hpp
    graphics_view/MAbstractItem.hpp
    graphics_view/MSourceItem.cpp
    graphics_view/MSourceItem.hpp
    graphics_view/MSourceItem.hpp
    graphics_view/MSinkItem.cpp
    graphics_view/MSinkItem.hpp
    graphics_view/MJunctionItem.cpp
    graphics_view/MJunctionItem.hpp
    graphics_view/MWellItem.cpp
    graphics_view/MWellItem.hpp
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
    QML_FILES ${QML_SRC}
    RESOURCES resources.qrc widget/SplashDialog.ui
    SOURCES
)

if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
    target_compile_definitions(MultiflowUI PRIVATE QT_QML_DEBUG)
endif ()

target_link_libraries(
    MultiflowUI
    PRIVATE
    MultiflowLibrary
    fluentuiplugin
    Qt6::Core
    Qt6::Gui
    Qt6::Charts
    Qt6::Widgets
    Qt6::Widgets
    Qt6::Quick
    Qt6::QuickWidgets
    Qt6::QuickControls2
)
