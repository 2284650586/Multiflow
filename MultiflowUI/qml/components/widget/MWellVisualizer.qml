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

    /**
     * length, innerMargin, thickness
     */
    required property var liners

    /**
     * altitude
     */
    required property var artificialLifts

    QtObject {
        id: g
        readonly property var headerDesignedHeight: 10
        readonly property var masterTopMargin: 15
        readonly property var chokeRectangleSize: 8
        readonly property var artificialLiftLongerSideLength: 24
        readonly property var artificialLiftShorterSideLength: 16

        readonly property var sideLeft: "Left"
        readonly property var sideRight: "Right"
        readonly property var normalTubularMargin: 1

        property var repeaterAltificialLifts: []
        property var headerActualHeight: 48
        property var headerActualWidth
        property var standardTextHeight

        // I don't know why there was an invisible margin
        readonly property var magicPadding: 14

        function designedToActual(designedHeight) {
            return designedHeight * g.headerActualHeight / g.headerDesignedHeight
        }

        function actualToDesigned(actualHeight) {
            return actualHeight * g.headerDesignedHeight / g.headerActualHeight
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
                        child.y = g.designedToActual(child.altitude) - g.standardTextHeight
                    }
                })
                control.onArtificialLiftsChanged.connect(() => {
                    for (let i = 0; i < g.repeaterAltificialLifts.count; ++i) {
                        const child = g.repeaterAltificialLifts.itemAt(i)
                        child.y = g.designedToActual(child.altitude) - g.standardTextHeight
                    }
                })
                control.onCasingsChanged.connect(() => {
                    for (let i = 0; i < repeaterAltitudeMarks.count; ++i) {
                        const child = repeaterAltitudeMarks.itemAt(i)
                        child.y = g.designedToActual(child.altitude) - g.standardTextHeight
                    }
                })
            }

            AltitudeMark {
                altitude: g.headerDesignedHeight
                displayAltitude: 0
            }

            Repeater {
                id: repeaterAltitudeMarks
                model: control.casings
                AltitudeMark {
                    required property var modelData
                    altitude: g.headerDesignedHeight + modelData.length
                    displayAltitude: modelData.displayLength
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
                                    child.y = g.designedToActual(child.altitude)
                                }
                            }
                        })
                    }

                    Loader {
                        width: parent.width
                        sourceComponent: control.hasChoke ? componentChoke : null
                        Component {
                            id: componentChoke
                            Choke {
                                altitude: 0
                                width: parent.width
                            }
                        }
                    }

                    RowLayout {
                        anchors.fill: parent
                        spacing: 0

                        ColumnLayout {
                            Layout.alignment: Qt.AlignRight | Qt.AlignTop
                            spacing: 1

                            Repeater {
                                id: repeaterLinerLeft
                                Layout.alignment: Qt.AlignRight | Qt.AlignTop
                                model: control.liners.length

                                Liner {
                                    required property var index
                                    property var modelData: control.liners[index]

                                    length: modelData.length - sumLinersLength(index)
                                    innerMargin: modelData.innerMargin
                                    thickness: modelData.thickness
                                    side: g.sideLeft
                                }
                            }
                        }

                        Item {
                            Layout.fillWidth: true
                        }

                        // 右侧Casings
                        ColumnLayout {
                            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                            spacing: 1

                            Repeater {
                                id: repeaterLinerRight
                                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                                model: control.liners.length

                                RowLayout {
                                    required property var index
                                    property var modelData: control.liners[index]

                                    spacing: 0

                                    Loader {
                                        width: parent.width
                                        sourceComponent: index === 0 ? componentArtificialLift : null
                                        Layout.alignment: Qt.AlignTop

                                        Component {
                                            id: componentArtificialLift

                                            Repeater {
                                                id: repeaterAltificialLifts
                                                model: control.artificialLifts

                                                Component.onCompleted: {
                                                    g.repeaterAltificialLifts = repeaterAltificialLifts
                                                }

                                                ArtificialLift {
                                                    required property var modelData
                                                    altitude: g.actualToDesigned(g.artificialLiftShorterSideLength) + modelData.topOffset
                                                    width: parent.width
                                                }
                                            }
                                        }
                                    }

                                    Liner {
                                        length: modelData.length - sumLinersLength(index)
                                        innerMargin: modelData.innerMargin
                                        thickness: modelData.thickness
                                        side: g.sideRight
                                    }
                                }
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
                            required property var index

                            Layout.alignment: Qt.AlignLeft | Qt.AlignTop

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

    function sumLinersLength(firstN) {
        let ret = 0
        for (let i = 0; i < Math.min(firstN, control.liners.length); ++i) {
            ret += control.liners[i].length
        }
        return ret
    }

    component AltitudeMark: Rectangle {
        required property var altitude
        required property var displayAltitude
        Layout.fillWidth: true

        ColumnLayout {
            spacing: 0

            FluText {
                text: `${displayAltitude} m`
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
        required property var altitude

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

    component ArtificialLift: Item {
        required property var altitude

        Rectangle {
            width: g.artificialLiftLongerSideLength - g.artificialLiftShorterSideLength
            height: g.artificialLiftLongerSideLength
            x: 0
            y: 0
            color: "darkgray"
        }

        Rectangle {
            width: g.artificialLiftLongerSideLength
            height: g.artificialLiftLongerSideLength - g.artificialLiftShorterSideLength
            x: -g.artificialLiftShorterSideLength
            y: g.artificialLiftShorterSideLength
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
        color: "darkblue"
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
