import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Multiflow.UI
import FluentUI

FluWindow {
    id: window
    width: 640
    height: 480
    visible: true
    title: "Multiflow"

    FluMenuBar {
        FluMenu {
            title: "文件"

            Action {
                text: "退出"
                onTriggered: dialogExit.open()
            }
        }
        FluMenu {
            title: "工具"

            Action {
                text: "打开公式查看器"
                onTriggered: vmWindowMain.onFormulaViewerButtonClicked()
            }
        }
    }

    FluButton {
        id: button
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }

    FluContentDialog {
        id: dialogExit
        title: "退出"
        message: "确认要退出 Multiflow 吗？"
        buttonFlags: FluContentDialogType.NegativeButton | FluContentDialogType.PositiveButton
        negativeText: "取消"
        positiveText: "退出"
        onPositiveClicked: window.close()
    }
}
