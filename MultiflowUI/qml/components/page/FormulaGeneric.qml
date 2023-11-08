import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Multiflow.UI
import FluentUI

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

    FluText {
        text: "公式描述"
        font: FluTextStyle.Subtitle
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
        FluCopyableText {
            text: formula.expression.representation
            font: FluTextStyle.BodyStrong
        }
    }

    FluText {
        text: "Lisp"
        font: FluTextStyle.Subtitle
    }
    Card {
        FluCopyableText {
            text: formula.lisp
            font: FluTextStyle.BodyStrong
        }
    }

    FluText {
        text: "自变量表"
        font: FluTextStyle.Subtitle
    }
    Card {
        Repeater {
            id: repeaterVariables
            model: formula.variables

            FluText {
                text: modelData.name + " - " + modelData.description
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
}
