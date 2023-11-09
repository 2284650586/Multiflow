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

            RowLayout {
                spacing: 8
                Layout.fillWidth: true

                FluText {
                    text: `${modelData.name} = `
                    font.pointSize: 11
                    font.weight: Font.DemiBold
                }
                FluTextBox {
                    text: `${environment.get(modelData.name)}`
                    maximumLength: 10
                    onTextChanged: {
                        onUpdateEnvironment(modelData.name, text)
                    }
                }
                HSpacer {}
                FluText {
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
                onClicked: {
                    onCalculate()
                }
            }
            FluButton {
                text: "图表"
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
}
