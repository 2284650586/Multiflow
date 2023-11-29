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
    width: 1400
    height: 800
    title: "管井数据"
    visible: true
    Component.onCompleted: {
        window.title += ` - ${well.general.value.name.value}`
        onDataChanged.connect(g.handleDataChange)
    }

    QtObject {
        id: g
        property var hasChoke: false

        function handleDataChange(entity) {
            hasChoke = getHasChoke()
            bridge.onDataChanged(entity)
        }

        function getHasChoke() {
            return ivAny(
                "downhole-equipment",
                "equipment", (v) => v === "Choke")
        }

        function ivAny(category, key, predicate) {
            const size = independentVariables.size(category)
            for (let i = 0; i < size; ++i) {
                if (predicate(independentVariables.get(category, i, key))) {
                    return true
                }
            }
            return false
        }
    }

    RowLayout {
        anchors.fill: parent
        anchors.margins: 10

        FluArea {
            Layout.preferredWidth: 400
            Layout.fillHeight: true
            border.color: Colors.border
            color: Colors.background

            MWellVisualizer {
                id: visualizer
                anchors.fill: parent
                anchors.margins: 10
                well: entity
                iv: independentVariables
                cu: calculationUnit
                hasChoke: g.hasChoke
            }
        }

        FluArea {
            Layout.fillWidth: true
            Layout.fillHeight: true
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
                    editor.onDataEvaluated.connect((results) => {
                        let resultString = ""
                        for (const result of results) {
                            resultString += `${result.map(p => `(${p[0]}, ${p[1]})`).join(", ")};\n`
                        }
                        showAlert("计算结果", resultString)
                        prepareChartViewer(results, "Q (STB/d)", "Pwf (psia)")
                    })
                }

                function prepareChartViewer(results, yName, xName) {
                    const xValues = []
                    const yValues = []
                    for (const series of results) {
                        const yValueSeries = []
                        const xValueSeries = []
                        for (const pair of series) {
                            yValueSeries.push(pair[1])
                            xValueSeries.push(pair[0])
                        }
                        yValues.push(yValueSeries)
                        xValues.push(xValueSeries)
                    }
                    showDiagram(category, yValues, xValues, yName, xName)
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

    FluContentDialog {
        property string dialogTitle
        property string dialogMessage

        id: dialog
        title: dialogTitle
        message: dialogMessage
        buttonFlags: FluContentDialogType.NeutralButton
        neutralText: "好"
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

    function showAlert(title, message) {
        dialog.dialogTitle = title
        dialog.dialogMessage = message
        dialog.open()
    }

    function addTab(title, control, args) {
        tabView.appendTab("qrc:/resources/image/linepointer.png", title, control, Object.assign({
            "title": title
        }, args))
    }
}
