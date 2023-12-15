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
    //! property var pvtIv
    //! property var pvtCategory
    //! property var pvtEntity
    //! property var pvtCalculationUnit

    signal onDataChanged(var entity)

    id: window
    width: 1200
    height: 800
    title: "高压物性计算"
    visible: true

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
                const argument = {}
                addTab('基本参数校核', tabGeneral, argument)
                addTab('拟合校正', tabFitting, argument)
                addTab('校正图形', tabCorrection, argument)
            }
        }
    }

    Component {
        id: tabGeneral

        MEntityEditorView {
            id: editor
            anchors.margins: 10
            anchors.fill: parent
            entity: pvtEntity
            iv: pvtIv
            calculationUnit: pvtCalculationUnit
            category: pvtCategory
            hideDefaultCalculateButton: true
            extraRowActions: getExtraRowActions()

            Component.onCompleted: {
                editor.onDataPartiallyChanged.connect(() => onDataChanged(pvtEntity))
                editor.onDataEvaluated.connect(handleDataEvaluated)
                pvtCalculationUnit.onError.connect(handleCalculationError)
            }

            function getExtraRowActions() {
                return [
                    {
                        text: '计算',
                        onClicked: (args) => {
                            const {category, iv, entity} = args
                            pvtCalculationUnit.update(entity, iv)
                            const results = pvtCalculationUnit.evaluate(category)
                            handleDataEvaluated(results)
                        }
                    }
                ]
            }

            function handleCalculationError(message) {
                showAlert("计算时遇到错误", message)
            }

            function handleDataEvaluated(results) {
                let resultString = ''
                for (let pressureIndex = 0; pressureIndex < results.length; ++pressureIndex) {
                    for (let temperatureIndex = 0; temperatureIndex < results[pressureIndex].length; ++temperatureIndex) {
                        const item = results[pressureIndex][temperatureIndex]
                        const [
                            pb,
                            Rs,
                            b0b,
                            miu0d,
                            miu0,
                            miuU,
                            miug,
                            miuw,
                            mium,
                            rho0,
                        ] = item.map((v) => v.toFixed(3))
                        const resultStringComponents = [
                            `饱和压力：${pb}`,
                            `溶解油气比：${Rs}`,
                            `原油体积系数：${b0b}`,
                            `地面脱气原油粘度：${miu0d}`,
                            `饱和原油粘度：${miu0}`,
                            `未饱和原油粘度：${miuU}`,
                            `气体粘度：${miug}`,
                            `水粘度：${miuw}`,
                            `油水混合物粘度：${mium}`,
                            `原油密度：${rho0}`,
                        ]
                        resultString += resultStringComponents.join('\n') + '\n\n'
                    }
                }
                showAlert("计算结果", resultString)
            }
        }
    }

    Component {
        id: tabFitting

        Text {
        }
    }

    Component {
        id: tabCorrection

        Text {
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
