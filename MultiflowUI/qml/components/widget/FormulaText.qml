import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Multiflow.UI
import FluentUI

FluCopyableText {
    id: control
    Layout.fillWidth: true
    font.family: "Consolas"
    font.weight: Font.DemiBold

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.IBeamCursor
        onClicked: control.selectAll()
    }
}
