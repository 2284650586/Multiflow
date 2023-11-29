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
    clip: true

    required property var well
    required property var iv
    required property var cu
    required property bool hasChoke

    /**
     * length, innerMargin, thickness
     */
    required property var casings

    QtObject {
        id: g
        readonly property var headerDesignedHeight: 10
        readonly property var masterTopMargin: 15
        readonly property var chokeRectangleSize: 8

        readonly property var sideLeft: "Left"
        readonly property var sideRight: "Right"
        readonly property var normalTubularMargin: 1

        property var headerActualHeight: 48
        property var headerActualWidth
        property var standardTextHeight

        // I don't know why there was an invisible margin
        readonly property var magicPadding: 14

        function designedToActual(designedHeight) {
            return designedHeight * g.headerActualHeight / g.headerDesignedHeight
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Item {
            id: heightColumn
            Layout.preferredWidth: parent.width / 3 - 48
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            Layout.topMargin: g.masterTopMargin
            Component.onCompleted: {
                g.onStandardTextHeightChanged.connect(() => {
                    for (let i = 0; i < children.length; ++i) {
                        const child = children[i]
                        child.y = g.designedToActual(child.altitute) - g.standardTextHeight
                    }
                    control.onCasingsChanged.connect(() => {
                        for (let i = 0; i < repeaterAltituteMarks.count; ++i) {
                            const child = repeaterAltituteMarks.itemAt(i)
                            child.y = g.designedToActual(child.altitute) - g.standardTextHeight
                        }
                    })
                })
            }

            AltituteMark {
                altitute: 0
                displayAltitute: -g.headerDesignedHeight
            }

            AltituteMark {
                altitute: g.headerDesignedHeight
                displayAltitute: 0
            }

            Repeater {
                id: repeaterAltituteMarks
                model: control.casings
                AltituteMark {
                    required property var modelData
                    altitute: g.headerDesignedHeight + modelData.length
                    displayAltitute: modelData.displayLength
                }
            }
        }

        ColumnLayout {
            id: headColumn
            Layout.preferredWidth: g.headerActualWidth + g.magicPadding
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            Layout.topMargin: g.masterTopMargin
            spacing: 0

            WellHeader {
                Layout.fillWidth: true
                Layout.preferredHeight: g.headerActualHeight
            }

            RowLayout {
                id: tubularsRow
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                spacing: 0

                RowLayout {
                    id: tubularsRowLeft
                    spacing: 0
                    Layout.fillWidth: true

                    Repeater {
                        model: control.casings
                        Casing {
                            required property var modelData

                            length: modelData.length
                            innerMargin: modelData.innerMargin
                            thickness: modelData.thickness
                            side: g.sideLeft
                        }
                    }

                    Item {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }
                }
                Item {
                    id: downholeEquipment
                    Layout.fillHeight: true
                    Layout.preferredWidth: g.headerActualWidth * 51 / 200
                    Component.onCompleted: {
                        g.onHeaderActualHeightChanged.connect(() => {
                            // 当所有子元素都加载完成后，手动调整它们的位置
                            for (let i = 0; i < children.length; ++i) {
                                let child = children[i]

                                // Loader?
                                if (child.item) {
                                    child = child.item
                                }
                                child.y = g.designedToActual(child.altitute)
                            }
                        })
                    }

                    Loader {
                        width: parent.width
                        sourceComponent: control.hasChoke ? componentChoke : null
                        Component {
                            id: componentChoke
                            Choke {
                                altitute: 0
                                width: parent.width
                            }
                        }
                    }
                }
                RowLayout {
                    id: tubularsRowRight
                    spacing: 0
                    Layout.fillWidth: true

                    Item {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }

                    Repeater {
                        model: control.casings && MUtils.reversed(control.casings)
                        Casing {
                            required property var modelData

                            length: modelData.length
                            innerMargin: modelData.innerMargin
                            thickness: modelData.thickness
                            side: g.sideRight
                        }
                    }
                }
            }
        }

        ColumnLayout {
            id: labelColumn
            Layout.preferredWidth: parent.width / 3 - 18
            Layout.fillHeight: true
            Layout.topMargin: g.masterTopMargin
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            spacing: 0
        }
    }

    component AltituteMark: Rectangle {
        required property var altitute
        required property var displayAltitute
        Layout.fillWidth: true

        ColumnLayout {
            spacing: 0

            FluText {
                text: `${displayAltitute} m`
                font.pixelSize: 12

                Component.onCompleted: {
                    if (!g.standardTextHeight) {
                        g.standardTextHeight = height + 1
                    }
                }
            }

            Rectangle {
                Layout.preferredWidth: 1000
                Layout.preferredHeight: 2
                Layout.fillWidth: true
                color: Colors.areaBorder
            }
        }
    }

    component WellHeader: Item {
        Image {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            fillMode: Image.PreserveAspectFit
            source: "qrc:/resources/image/header.png"

            Component.onCompleted: {
                g.headerActualHeight = height
                g.headerActualWidth = width
            }
        }
    }

    component Choke: Item {
        required property var altitute

        Rectangle {
            width: g.chokeRectangleSize
            height: g.chokeRectangleSize
            x: 0
            y: 0
            color: "darkgray"
        }

        Rectangle {
            width: g.chokeRectangleSize
            height: g.chokeRectangleSize
            x: parent.width - g.chokeRectangleSize
            y: 0
            color: "darkgray"
        }
    }

    component Casing: Rectangle {
        required property var length
        required property var innerMargin
        required property var thickness
        required property var side

        property var calculatedLength: g.designedToActual(length)
        Layout.leftMargin: side === g.sideRight ? innerMargin : g.normalTubularMargin
        Layout.rightMargin: side === g.sideLeft ? innerMargin : g.normalTubularMargin
        Layout.preferredHeight: calculatedLength
        Layout.preferredWidth: thickness
        Layout.alignment: Qt.AlignTop
        color: "gray"
        border.color: "black"
    }

    component Liner: Rectangle {
        required property var length
        required property var innerMargin
        required property var thickness
        required property var side

        property var calculatedLength: g.designedToActual(length)
        Layout.leftMargin: side === g.sideRight ? innerMargin : g.normalTubularMargin
        Layout.rightMargin: side === g.sideLeft ? innerMargin : g.normalTubularMargin
        Layout.preferredHeight: calculatedLength
        Layout.preferredWidth: thickness
        Layout.alignment: Qt.AlignTop
        color: "gray"
        border.color: "black"
    }

    component OpenHole: Rectangle {
        required property var length
        required property var innerMargin
        required property var thickness
        required property var side

        property var calculatedLength: g.designedToActual(length)
        Layout.leftMargin: side === g.sideRight ? innerMargin : g.normalTubularMargin
        Layout.rightMargin: side === g.sideLeft ? innerMargin : g.normalTubularMargin
        Layout.preferredHeight: calculatedLength
        Layout.preferredWidth: thickness
        Layout.alignment: Qt.AlignTop
        color: "gray"
        border.color: "black"
    }
}
