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

    ListView {
        anchors.fill: parent
        model: windowMain.formulae

        delegate: Rectangle {
            width: parent.width
            height: 50
            color: "lightblue"

            Text {
                text: modelData.name + " ~ " + modelData.description + " ~ " + modelData.expression.name
                anchors.centerIn: parent
            }
        }
    }

    TextField {
        id: input
        anchors.centerIn: parent
    }

    Button {
        text: input.text
        anchors.bottom: parent.bottom
        leftPadding: 24
        rightPadding: 24
        topPadding: 12
        bottomPadding: 12
        onClicked: {
            if (UIUtils.confirm("确认要退出 Multiflow 吗？", "退出", "取消")) {
                window.close()
            }
        }
    }
}
