import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Multiflow.UI
import FluentUI

FluPaneItem {
  property var navigationView
  property var formula

  title: formula.name
  desc: formula.description
  icon: FluentIcons.List
  onTap: {
    // 先Push到空页面，从而迫使URL变化，然后再push到正确的页面
    // 这么做是因为FluentUI作者的设计，URL相同的页面不会重新加载参数
    navigationView.push("")
    navigationView.push("qrc:/qml/components/page/FormulaGeneric.qml", {
      formula: formula,
    })
  }
}
