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
                addTab('基础参数', tabGeneral, argument)
                addTab('参数校核', tabParameterCheck, argument)
                addTab('拟合校正', tabFitting, argument)
                addTab('校正图形', tabCorrection, argument)
            }
        }
    }

    Component {
        id: tabParameterCheck

        Text {}
    }

    Component {
        id: tabFitting

        Text {}
    }

    Component {
        id: tabCorrection

        Text {}
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

            Component.onCompleted: {
                editor.onDataPartiallyChanged.connect(() => onDataChanged(pvtEntity))
            }
        }
    }

    function addTab(title, control, args) {
        tabView.appendTab("qrc:/resources/image/linepointer.png", title, control, Object.assign({
            "title": title
        }, args))
    }
}
