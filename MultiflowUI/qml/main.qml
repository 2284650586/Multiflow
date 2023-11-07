import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Multiflow.UI

ApplicationWindow {
    id: window
    width: 640
    height: 480
    visible: true
    title: "Multiflow"
    menuBar: MenuBar {
        Menu {
            title: "文件(&F)"

            MenuItem {
                text: "退出(&E)"
                onTriggered: handleExit()
            }
        }

        Menu {
            title: "工具(&U)"

            MenuItem {
                text: "打开公式查看器(&F)"
                onTriggered: vmWindowMain.onFormulaViewerButtonClicked()
            }
        }
    }

    function handleExit() {
        if (UIUtils.confirm("确认要退出 Multiflow 吗？", "退出", "取消")) {
            window.close()
        }
    }
}
