import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Multiflow.UI
import FluentUI
import Qt.labs.qmlmodels
import "qrc:/qml/components/widget/"
import "qrc:/qml/components/singleton/"

Item {
    required property var entity
    required property var bridge
    //! property var fluidIv
    //! property var fluidEntity
    property var fluidCategory: "BlackOil"
    height: 70

    signal onOpenFluidManager()

    QtObject {
        id: g

        property var fluidNames: []
        property var shouldShowRefresh: false

        function getFluidNames() {
            const names = []
            const size = fluidIv.size(fluidCategory)
            for (let i = 0; i < size; ++i) {
                const fluidName = fluidIv.get(fluidCategory, i, 'name')
                names.push(fluidName)
            }
            return names
        }

        function refreshData() {
            fluidNames = getFluidNames()
        }

        Component.onCompleted: {
            onOpenFluidManager.connect(bridge.onOpenBlackOilManager)
        }
    }

    Component.onCompleted: {
        Qt.callLater(g.refreshData)
    }

    ColumnLayout {
        RowLayout {
            Layout.fillWidth: true

            FluText {
                text: "选择液体模型: "
            }

            Loader {
                sourceComponent: g.fluidNames.length > 0 ? componentComboBox : componentEmpty
            }

            FluButton {
                text: g.fluidNames.length > 0 ? "编辑" : "去添加"
                onClicked: {
                    onOpenFluidManager()
                    g.shouldShowRefresh = true
                }
            }

            FluButton {
                visible: g.shouldShowRefresh
                text: "刷新"
                onClicked: {
                    g.refreshData()
                }
            }

            Component {
                id: componentEmpty

                FluText {
                    text: "无，"
                }
            }

            Component {
                id: componentComboBox

                FluComboBox {
                    model: g.fluidNames
                    currentIndex: -1
                    Component.onCompleted: {
                        let name = entity.associateValue
                        if (!name) {
                            entity.associateValue = g.fluidNames[0]
                            name = entity.associateValue
                        }
                        const index = model.indexOf(name)
                        currentIndex = index
                    }
                }
            }

        }
    }
}
