import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Multiflow.UI
import FluentUI
import Qt.labs.qmlmodels
import "qrc:/qml/components/widget/"
import "qrc:/qml/components/singleton/"

FluentExtTableView {
  // categoryToHfKeys, iv, entity, category
  property var argument
  property var onNotifyDataChange

  id: tableView
  radius: 8
  color: "transparent"
  anchors.fill: parent
  anchors.leftMargin: -1
  columnSource: getColumnSource()

  Component {
    id: componentActionArea
    RowLayout {
      anchors.fill: parent

      FluButton {
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        text: "删除"
        onClicked: {
          tableView.closeEditor()
          argument.iv.remove(argument.category, row)
          onNotifyDataChange()
        }
      }
    }
  }

  function getColumnSource() {
    const columns = []
    for (const key of argument.categoryToHfKeys[argument.category]) {
      const property = argument.entity[key]
      columns.push({
        title: property.name,
        type: property.type,
        extra: property.extra,
        dataIndex: key,
        minimumWidth: 100,
        maximumWidth: 300,
        width: 90,
      })
    }
    columns.push({
      title: "操作",
      dataIndex: "action",
    })
    return columns
  }

  function readFromIv() {
    const rows = []
    const size = argument.iv.size(argument.category)
    for (let i = 0; i < size; ++i) {
      const row = {}
      for (const key of argument.categoryToHfKeys[argument.category]) {
        row[key] = argument.iv.get(argument.category, i, key) || '0'
      }
      row['action'] = tableView.customItem(componentActionArea)
      rows.push(row)
    }
    return rows
  }

  function refreshData() {
    tableView.dataSource = readFromIv()
  }
}
