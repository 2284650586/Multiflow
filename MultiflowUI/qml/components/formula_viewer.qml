import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Multiflow.UI

ApplicationWindow {
    id: window
    width: 640
    height: 480
    visible: true
    title: "Multiflow - 公式查看器"

    property int selectedIndex: vmFormulaViewer.selectedFormulaIndex
    property var currentFormula: selectedIndex === -1 ? null : vmFormulaViewer.formulae[selectedIndex]

    Row {
        anchors.fill: parent

        ListView {
            id: listView
            width: parent.width * 0.3
            height: parent.height
            model: vmFormulaViewer.formulae

            delegate: ItemDelegate {
                width: listView.width
                height: text1.implicitHeight + text2.implicitHeight + 12
                checked: index === selectedIndex
                onClicked: selectedIndex = index
                onCheckedChanged: checked && (selectedIndex = index)

                Row {
                    anchors.centerIn: parent
                    spacing: 2

                    Rectangle {
                        width: 4
                        height: parent.height
                        color: checked ? "lightgray" : "transparent"
                    }
                    Column {
                        spacing: 1

                        Text {
                            id: text1
                            text: "Item " + (index + 1)
                            color: "#212121"
                        }

                        Text {
                            id: text2
                            text: "Description for item " + (index + 1)
                            color: "#757575"
                            font.pixelSize: text1.font.pixelSize - 2
                        }
                    }
                }
            }
        }

        Rectangle {
            width: parent.width * 0.7
            height: parent.height
            color: "lightgray"

            Text {
                text: currentFormula
                    ? currentFormula.expression.name
                    : "No formula selected"
                anchors.centerIn: parent
            }
        }
    }
}
