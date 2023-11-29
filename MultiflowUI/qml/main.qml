import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Multiflow.UI
import FluentUI

Item {
    id: app

    Connections {
        target: FluTheme

        function onDarkModeChanged() {
            SettingsHelper.setDarkMode(FluTheme.darkMode)
        }
    }

    Connections {
        target: FluApp

        function onVsyncChanged() {
            SettingsHelper.setVsync(FluApp.vsync)
        }
    }

    Component.onCompleted: {
        FluApp.init(app)
        FluApp.vsync = SettingsHelper.getVsync()
        FluTheme.darkMode = SettingsHelper.getDarkMode()
        FluTheme.enableAnimation = true
        FluTheme.nativeText = false
        FluTextStyle.Body = Qt.font({
            family: MUtils.fontFamily,
            italic: false,
            pointSize: 10,
        })
        FluTextStyle.Subtitle = Qt.font({
            family: MUtils.fontFamily,
            italic: false,
            pointSize: 12,
        })
        FluTextStyle.TitleLarge = Qt.font({
            family: MUtils.fontFamily,
            italic: false,
            pointSize: 16,
        })
        FluApp.routes = {
            "/formula-viewer": "qrc:/qml/components/window/FormulaViewer.qml",
            "/well-editor": "qrc:/qml/components/window/WellEditor.qml",
            "/fluid-manager": "qrc:/qml/components/window/FluidManager.qml",
            "/pvt-calculator": "qrc:/qml/components/window/PvtCalculator.qml",
        }
        FluApp.run()
    }
}
