import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Multiflow.UI
import FluentUI
import Qt.labs.qmlmodels
import "qrc:/qml/components/widget/"
import "qrc:/qml/components/singleton/"

FluWindow {
    //! property var independentVariables
    property var cu: calculationUnit
    property var well: entity

    signal onDataChanged(var entity)

    id: window
    width: 1200
    height: 600
    title: "管井数据"
    visible: true

    Component.onCompleted: {
        window.title += ` - ${well.general.value.name.value}`
        onDataChanged.connect(bridge.onDataChanged)
    }

    FluArea {
        anchors.fill: parent
        anchors.margins: 10
        border.color: Colors.border
        color: Colors.background
        radius: 8
        clip: true

        FluTabView {
            id: tabView
            addButtonVisibility: FluTabViewType.Nerver // 啊，这不是我拼错的啊
            closeButtonVisibility: FluTabViewType.Nerver
            anchors.fill: parent
            Component.onCompleted: handleCreateTabs()

            function handleCreateTabs() {
                for (const key of well.keys()) {
                    const argument = {category: key, entity: well[key].value}
                    addTab(well[key].name, tab, argument)
                }
            }
        }
    }

    Component {
        id: tab

        MEntityEditorView {
            id: editor
            anchors.fill: parent
            anchors.margins: 10

            entity: argument.entity
            iv: independentVariables
            calculationUnit: cu
            category: argument.category

            Component.onCompleted: {
                editor.onDataPartiallyChanged.connect(() => onDataChanged(well))
            }
        }
    }

    function addTab(title, control, args) {
        tabView.appendTab("qrc:/resources/image/linepointer.png", title, control, Object.assign({
            "title": title
        }, args))
    }
}
