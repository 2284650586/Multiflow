import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Multiflow.UI
import FluentUI
import "qrc:/qml/components/singleton/"

FluWindow {
    id: window
    width: 800
    height: 600
    visible: true
    title: "Multiflow - 公式查看器"

    property int selectedIndex: vmFormulaViewer.selectedFormulaIndex
    property var currentFormula: selectedIndex === -1 ? null : vmFormulaViewer.formulae[selectedIndex]

    FluNavigationView {
        id: navigationView
        anchors.fill: parent
        pageMode: FluNavigationViewType.NoStack
        displayMode: FluNavigationViewType.Open
        items: FormulaItemsSingleton
        topPadding: FluTools.isMacos() ? 20 : 5
        title: "公式库"
        autoSuggestBox: FluAutoSuggestBox {
            width: 280
            anchors.centerIn: parent
            iconSource: FluentIcons.Search
            items: FormulaItemsSingleton.getSearchData()
            placeholderText: "搜索公式..."
            onItemClicked: (data) => {
                FormulaItemsSingleton.startPageByItem(data)
            }
        }

        Component.onCompleted: {
            FormulaItemsSingleton.navigationView = navigationView
            FormulaItemsSingleton.formulae = vmFormulaViewer.formulae
            FormulaItemsSingleton.render()
            setCurrentIndex(0)
        }
    }
}
