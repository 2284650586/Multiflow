import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Multiflow.UI
import FluentUI
import "qrc:/qml/components/widget"

FluScrollablePage {
    property var formula

    title: formula.name

    component Card: FluArea {
        default property alias subdata : itemContainer.data

        id: card
        Layout.bottomMargin: 10
        Layout.fillWidth: true
        paddings: 10
        height: 40
        leftPadding: 15

        ColumnLayout {
            id: itemContainer

            Component.onCompleted: {
                card.height = itemContainer.height + 20
            }
        }
    }

    QmlEnvironment {
        id: environment
        variableNames: formula.variables.map(v => v.name)
    }

    Card {
        FluText {
            text: formula.description
            font: FluTextStyle.Body
        }
    }

    FluText {
        text: "表达式"
        font: FluTextStyle.Subtitle
    }
    Card {
        FormulaText {
            text: formula.expression.representation
        }
    }

    FluText {
        text: "Lisp"
        font: FluTextStyle.Subtitle
    }
    Card {
        FormulaText {
            text: formula.lisp
        }
    }

    FluText {
        text: "代入"
        font: FluTextStyle.Subtitle
    }
    Card {
        Layout.alignment: Qt.AlignCenter

        Repeater {
            id: repeaterVariables
            model: formula.variables

            Row {
                property var initialText: `${environment.get(modelData.name)}`

                spacing: 8
                Layout.fillWidth: true

                FluText {
                    anchors.verticalCenter: parent.verticalCenter
                    text: `${modelData.name} = `
                    font.pointSize: 11
                    font.weight: Font.DemiBold
                    horizontalAlignment: Text.AlignRight
                    width: 80
                }
                FluTextBox {
                    id: textBox
                    anchors.verticalCenter: parent.verticalCenter
                    text: initialText
                    width: 120
                    maximumLength: 10
                    onTextChanged: {
                        onUpdateEnvironment(modelData.name, text)
                    }
                }
                HSpacer {}
                FluText {
                    anchors.verticalCenter: parent.verticalCenter
                    text: `(${modelData.description})`
                    color: "gray"
                }
            }
        }

        RowLayout {
            spacing: 8
            Layout.fillWidth: true

            FluText {
                text: `f(${ formula.variables.map(v => v.name).join(", ") }) = `
                font.pointSize: 11
            }
            FormulaText {
                id: textResult
                text: "-"
            }
        }

        FluDivider {}
        Row {
            spacing: 8

            FluButton {
                text: "计算"
                onClicked: onCalculate()
            }
            FluButton {
                text: "图表"
            }
            FluButton {
                text: "清空"
                onClicked: onClear()
            }
        }
    }


    FluText {
        text: "常数表"
        font: FluTextStyle.Subtitle
    }
    Card {
        Loader {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Component {
                id: anyConstants
                Repeater {
                    id: repeaterConstants
                    model: formula.constants

                    FluText {
                        text: modelData.name + " (" + modelData.description + ") = " + modelData.value
                        font: FluTextStyle.Body
                    }
                    Component.onCompleted: {
                        parent.parent.height = repeaterConstants.height + 20
                    }
                }
            }
            Component {
                id: noConstant
                FluText {
                    text: "无"
                    font: FluTextStyle.Body
                }
            }
            sourceComponent: formula.constants.length > 0 ? anyConstants : noConstant
        }
    }

    function _isNumeric(str) {
        if (typeof str != "string") {
            return false
        }
        return !isNaN(str) && !isNaN(parseFloat(str))
    }

    function onUpdateEnvironment(key, value) {
        if (!_isNumeric(value)) {
            return
        }
        environment.set(key, parseFloat(value))
    }

    function onCalculate() {
        textResult.text = `${formula.expression.evaluate(environment)}`
    }

    function onClear() {
        environment.resetValues();
        var count = repeaterVariables.count
        console.log(count)
        for (var i = 0; i < count; i++) {
            repeaterVariables.itemAt(i).initialText = ""
        }
    }
}
