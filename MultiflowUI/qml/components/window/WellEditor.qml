import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Multiflow.UI
import FluentUI
import Qt.labs.qmlmodels
import "qrc:/qml/components/widget/"
import "qrc:/qml/components/window/"
import "qrc:/qml/components/singleton/"

FluWindow {
    //! property var independentVariables
    property var cu: calculationUnit
    property var well: entity

    signal onDataChanged(var entity)

    id: window
    width: 1200
    height: 800
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
                const keys = MUtils.wrapMEntityKeys(well.keys())
                for (const key of keys) {
                    const argument = {category: key, entity: well[key].value}
                    addTab(well[key].name, tab, argument)
                }
            }
        }
    }

    Component {
        id: tab

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 10

            Loader {
                property var args: argument
                property var signalBridge: bridge
                sourceComponent: argument.category === 'completions' ? componentCompletion : null
            }

            MEntityEditorView {
                id: editor
                Layout.fillWidth: true
                Layout.fillHeight: true
                entity: argument.entity
                iv: independentVariables
                calculationUnit: cu
                category: argument.category

                Component.onCompleted: {
                    editor.onDataPartiallyChanged.connect(() => onDataChanged(well))
                    editor.onDiagramRequested.connect(showDiagram)
                }
            }
        }
    }

    Component {
        id: componentCompletion

        MCompletionsView {
            id: completions
            Layout.fillWidth: true
            Layout.fillHeight: true
            entity: args.entity
            bridge: signalBridge
        }
    }

    function showDiagram(category, yValues, xValues, yName, xName) {
        const component = Qt.createComponent("qrc:/qml/components/window/ChartViewer.qml")
        if (component.status === Component.Ready) {
            const chartViewer = component.createObject(window, {
                category: category,
                yValues: yValues,
                xValues: xValues,
                yName: yName,
                xName: xName,
            })
            chartViewer.show()
        }
    }

    function addTab(title, control, args) {
        tabView.appendTab("qrc:/resources/image/linepointer.png", title, control, Object.assign({
            "title": title
        }, args))
    }
}
