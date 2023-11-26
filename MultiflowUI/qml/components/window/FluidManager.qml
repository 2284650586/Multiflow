import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Multiflow.UI
import FluentUI
import Qt.labs.qmlmodels
import "qrc:/qml/components/widget/"
import "qrc:/qml/components/singleton/"

FluWindow {
    //! property var fluidIv
    //! property var fluidCategory
    //! property var fluidEntity

    id: window
    width: 800
    height: 600
    title: "液体数据管理"
    visible: true

    Component.onCompleted: {
        window.title += ` - ${fluidCategory}`
    }

    FluArea {
        anchors.fill: parent
        anchors.margins: 10
        border.color: Colors.border
        color: Colors.background
        radius: 8
        clip: true

        MEntityEditorView {
            id: editor
            anchors.fill: parent
            anchors.margins: 10

            entity: fluidEntity
            iv: fluidIv
            calculationUnit: null
            category: fluidCategory

            Component.onCompleted: {
                console.log(`Fluid count: ${fluidCategory} = ${fluidIv.size(fluidCategory)}`)
                editor.onDataPartiallyChanged.connect(() => {})
            }
        }
    }
}
