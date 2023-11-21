import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Multiflow.UI
import FluentUI
import "qrc:/qml/components/widget/"

FluWindow {
  id: window
  width: 800
  height: 600
  visible: true
  title: "Multiflow - 公式查看器"

  property int selectedIndex: vmFormulaViewer.selectedFormulaIndex
  property var currentFormula: selectedIndex === -1 ? null : vmFormulaViewer.formulae[selectedIndex]
  property var formulae: vmFormulaViewer.formulae

  NavigationView {
    id: navigationView
    visible: true
    anchors.fill: parent
    displayMode: FluNavigationViewType.Open
    model: formulae
    topPadding: FluTools.isMacos() ? 20 : 5
    title: "公式库"
    autoSuggestBox: AutoSuggestBox {
      width: 280
      anchors.centerIn: parent
      iconSource: FluentIcons.Search
      placeholderText: "搜索公式..."
      items: getSearchData()
      onItemClicked: item => navigateToFormula(item.data)
    }
    itemDelegate: (formula, index) => {
      return {
        _parent: null,
        disabled: false,
        title: formula.name,
        tap: () => {
          navigateToFormula(formula)
        }
      }
    }
    Component.onCompleted: {
      if (formulae.length > 0) {
        setCurrentIndex(0)
        navigateToFormula(formulae[0])
      }
    }
  }

  function navigateToFormula(formula) {
    navigationView.push("")
    navigationView.push("qrc:/qml/components/page/FormulaGeneric.qml", {
      formula: formula,
    })
  }

  /**
   * @brief ES5 version of `formulae.map(f => {title: f.name. ...f})`
   */
  function getSearchData() {
    let ret = []
    for (const f of formulae) {
      ret.push({title: f.name, data: f})
    }
    return ret
  }
}
