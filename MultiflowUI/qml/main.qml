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

    Button {
        text: "嘟嘟嘟"
        anchors.centerIn: parent
        leftPadding: 24
        rightPadding: 24
        topPadding: 12
        bottomPadding: 12
        onClicked: {
            if (uiUtils.confirm("确认要退出 Multiflow 吗？", "退出", "取消")) {
                window.close()
            }
        }
    }

    UIUtils {
        id: uiUtils
    }
}
