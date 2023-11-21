import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Multiflow.UI
import FluentUI
import "qrc:/qml/components/widget/"
import "qrc:/qml/components/singleton/"

FluWindow {
    id: window

    height: 800
    title: "管井数据"
    visible: true
    width: 1280

    Component.onCompleted: {
        console.log(`Bind well: ${well.keys()}`)
    }

    RowLayout {
        anchors.fill: parent
        anchors.margins: 10

        Rectangle {
            Layout.fillHeight: true
            color: "darkgray"
            radius: 8
            width: 300
        }
        FluArea {
            Layout.fillHeight: true
            Layout.fillWidth: true
            border.color: FluColors.border
            color: FluColors.background
            radius: 8

            FluTabView {
                id: tabView

                addButtonVisibility: FluTabViewType.Nerver
                closeButtonVisibility: FluTabViewType.Nerver

                Component.onCompleted: {
                    _addTab("基本信息", tabGeneral, {});
                    _addTab("Deviation", tabDeviation, {});
                    _addTab("热传递", tabGeneral, {});
                    _addTab("管井", tabGeneral, {});
                    _addTab("井下设备", tabGeneral, {});
                    _addTab("举升", tabGeneral, {});
                    _addTab("仿真", tabGeneral, {});
                }
            }

            // Background
            Rectangle {
                anchors.fill: parent
                color: "transparent"
                radius: 8
            }
        }
    }

    Component {
        id: tabGeneral

        TabContent {
            FluText {
                text: argument.title
            }
            FluButton {
                text: "好啊"
            }
        }
    }

    Component {
        id: tabDeviation

        TabContent {
            FluText {
                text: argument.title
            }
        }
    }

    component TabContent: Item {
        id: content

        default property alias content: contentView.data

        anchors.fill: parent
        anchors.margins: 10

        ColumnLayout {
            id: contentView

        }
    }

    function _addTab(title, control, args) {
        tabView.appendTab("qrc:/resources/image/linepointer.png", title, control, Object.assign({
            "title": title
        }, args));
    }
}
