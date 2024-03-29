cmake_minimum_required(VERSION 3.27)

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
aux_source_directory(utils utils)
aux_source_directory(utils/delegate UTIL_DELEGATE)
aux_source_directory(utils/validator UTIL_VALIDATOR)
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
    entity/common.hpp
    parser/EntityParser.cpp
    parser/EntityParser.hpp
    entity/MEntity.cpp
    entity/MEntity.hpp
    service/EntityService.cpp
    service/EntityService.hpp
    service/EntityService.hpp
    utils/YamlUtils.cpp
    utils/YamlUtils.hpp
    utils/YamlUtils.hpp
    unit_converter/LengthConverter.cpp
    unit_converter/LengthConverter.hpp
    unit_converter/LengthConverter.hpp
    unit_converter/AbstractUnitConverter.cpp
    unit_converter/AbstractUnitConverter.hpp
    unit_converter/AbstractUnitConverter.hpp
    qml/bridge/MSignalBridge.hpp
    qml/bridge/MSignalBridge.cpp
    qml/utils/QmlFormulaUtils.cpp
    qml/utils/QmlFormulaUtils.hpp
    qml/utils/QmlFormulaUtils.hpp
    entity/MIndependentVariables.cpp
    entity/MIndependentVariables.hpp
    entity/MIndependentVariables.hpp
    entity/unit/generic/AbstractCalculationUnit.cpp
    entity/unit/generic/AbstractCalculationUnit.hpp
    entity/unit/WellCalculationUnit.cpp
    entity/unit/WellCalculationUnit.hpp
    entity/unit/WellCalculationUnit.hpp
    graphics_view/window/MWellDisplayWindow.cpp
    graphics_view/window/MWellDisplayWindow.hpp
    graphics_view/window/MWellDisplayWindow.ui
    graphics_view/window/MWellDisplayWindow.cpp
    graphics_view/well/MWellHead.cpp
    graphics_view/well/MWellHead.hpp
    helper/CoordinateHelper.cpp
    helper/CoordinateHelper.hpp
    graphics_view/well/MWellGeneric.cpp
    graphics_view/well/MWellGeneric.hpp
    helper/MEntityHelper.cpp
    helper/MEntityHelper.hpp
    unit_converter/PressureConverter.cpp
    unit_converter/PressureConverter.hpp
    unit_converter/TemperatureConverter.cpp
    unit_converter/TemperatureConverter.hpp
    unit_converter/FluidUnitConverter.cpp
    unit_converter/FluidUnitConverter.hpp
    unit_converter/GasRatioConverter.cpp
    unit_converter/GasRatioConverter.hpp
    unit_converter/RatioFractionConverter.cpp
    unit_converter/RatioFractionConverter.hpp
    service/FluidDataService.cpp
    service/FluidDataService.hpp
    service/PVTService.cpp
    service/PVTService.hpp
    entity/unit/PvtCalculationUnit.cpp
    entity/unit/PvtCalculationUnit.hpp
    unit_converter/TimeConverter.cpp
    unit_converter/TimeConverter.hpp
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

if(MSVC)
    target_compile_options(MultiflowUI PRIVATE "/utf-8")
endif()

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
    yaml-cpp
    fmt
)
