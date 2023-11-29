import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Multiflow.UI
import FluentUI
import Qt.labs.qmlmodels
import "qrc:/qml/components/widget/"
import "qrc:/qml/components/window/"
import "qrc:/qml/components/singleton/"

Item {
    id: control

    required property var well
    required property var iv
    required property var cu

    ColumnLayout {
        id: headColumn
        spacing: 0
        anchors.fill: parent

        Text {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            text: "Where am I?"
        }
    }
}
