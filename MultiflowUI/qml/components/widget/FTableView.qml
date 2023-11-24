import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Basic
import QtQuick.Layouts
import Qt.labs.qmlmodels
import FluentUI
import "qrc:/qml/components/singleton/"

Rectangle {
  property var columnSource
  property var dataSource
  property color borderColor: Colors.areaBorder
  property alias tableModel: table_model
  id: control
  color: FluTheme.dark ? Qt.rgba(39 / 255, 39 / 255, 39 / 255, 1) : Qt.rgba(251 / 255, 251 / 255, 253 / 255, 1)

  signal cellUpdated(int row, int column, var value)

  onColumnSourceChanged: {
    if (columnSource.length !== 0) {
      var com_column = Qt.createComponent("FTableModelColumn.qml")
      if (com_column.status === Component.Ready) {
        var columns = []
        var header_rows = {}
        columnSource.forEach(function (item) {
          var column = com_column.createObject(table_model, {display: item.dataIndex});
          columns.push(column)
          header_rows[item.dataIndex] = item.title
        })
        table_model.columns = columns
        header_model.columns = columns
        d.header_rows = [header_rows]
      }
    }
  }
  QtObject {
    id: d
    property var currentRow
    property int rowHoverIndex: -1
    property int defaultItemWidth: 100
    property int defaultItemHeight: 42
    property var header_rows: []
    property var isEditing: false

    function obtEditDelegate(column, row, cellItem) {
      var display = table_model.data(table_model.index(row, column), "display")
      var cellPosition = cellItem.mapToItem(scroll_table, 0, 0)
      item_loader.column = column
      item_loader.row = row
      item_loader_layout.cellItem = cellItem
      item_loader_layout.x = table_view.contentX + cellPosition.x
      item_loader_layout.y = table_view.contentY + cellPosition.y
      item_loader_layout.width = table_view.columnWidthProvider(column)
      item_loader_layout.height = table_view.rowHeightProvider(row)
      item_loader.display = display
      item_loader.currentItem = table_model.getRow(row)
      var obj = columnSource[column].editDelegate
      if (obj) {
        return obj
      }
      if (columnSource[column].editMultiline === true) {
        return com_edit_multiline
      }

      const type = columnSource[column].type
      item_loader.currentProperty = columnSource[column]
      if (typeof (type) === 'string' && type.startsWith("Builtin.")) {
        if (columnSource[column].extra) {
          return com_conv
        }
        return com_loading
      }
      if (type === 'enum') {
        return com_combo
      }
      return com_edit
    }
  }
  onDataSourceChanged: {
    table_model.clear()
    for (var i = 0; i < dataSource.length; i++) {
      var row = dataSource[i]
      row.__index = i
      table_model.appendRow(row)
    }
  }
  TableModel {
    id: table_model
  }
  Component {
    id: com_edit
    FCellTextField {
      id: text_box
      text: display
      readOnly: true === columnSource[column].readOnly
      Component.onCompleted: {
        forceActiveFocus()
        selectAll()
      }

      // 特制的逻辑，点击外部也视同为提交
      Component.onDestruction: {
        save()
      }
      onCommit: {
        save()
      }

      function save() {
        if (!readOnly) {
          display = text_box.text
        }
        cellUpdated(row, column, text_box.text)
        tableView.closeEditor()
      }
    }
  }
  Component {
    id: com_loading

    RowLayout {
      anchors.fill: parent
      spacing: 0

      FluText {
        text: "Loading..."
      }
    }
  }
  Component {
    id: com_conv

    RowLayout {
      property var units: currentProperty.extra.units()
      property var initialUnit: units.indexOf(currentValue)
      anchors.fill: parent
      spacing: 0

      Item {
        Layout.preferredWidth: 6
      }

      FCellTextField {
        id: textBox
        readOnly: true === columnSource[column].readOnly
        cleanEnabled: false
        Layout.preferredHeight: 30
        Layout.fillWidth: true
        Component.onCompleted: {
          forceActiveFocus()
          selectAll()
          textBox.text = currentValue
        }
        Component.onDestruction: {
          save()
        }
        onCommit: {
          save()
        }
      }

      FluComboBox {
        property var lastUnit: currentProperty.associateValue ? units[currentProperty.associateValue] : units[0]

        id: comboBox
        model: units
        width: 30
        indicator: null
        Layout.preferredHeight: 30
        Layout.preferredWidth: 30
        onCurrentTextChanged: {
          if (!_isNumeric(textBox.text)) {
            return
          }
          let oldValue = parseFloat(textBox.text)
          let newUnit = currentText
          let newValue = currentProperty.extra.convert(oldValue, lastUnit, newUnit)
          newValue = Number(newValue.toFixed(2))
          textBox.text = `${newValue}`
          currentProperty.associateValue = currentIndex
          lastUnit = currentText
        }

        Component.onCompleted: {
          comboBox.currentIndex = currentProperty.associateValue ? currentProperty.associateValue : 0
        }
      }

      Item {
        Layout.preferredWidth: 6
      }

      function _isNumeric(str) {
        if (typeof str != "string") {
          return false
        }
        return !isNaN(str) && !isNaN(parseFloat(str))
      }

      function save() {
        cellUpdated(row, column, textBox.text)
        tableView.closeEditor()
      }
    }
  }
  Component {
    id: com_combo

    RowLayout {
      anchors.fill: parent
      spacing: 0

      Item {
        Layout.preferredWidth: 6
      }

      FluComboBox {
        property var items: currentProperty.extra.split(", ")
        property var initialIndex: items.indexOf(currentValue)

        id: combo_box
        model: items
        Layout.fillWidth: true
        Layout.preferredHeight: 30

        onCurrentTextChanged: {
          if (items.includes(currentText)) {
            save(currentText)
          }
        }
        Component.onCompleted: {
          forceActiveFocus()
          combo_box.currentIndex = initialIndex !== -1 ? initialIndex : 0
        }

        function save(text) {
          // currentValue = text
          cellUpdated(row, column, text)
          tableView.closeEditor()
        }
      }

      Item {
        Layout.preferredWidth: 6
      }
    }
  }
  Component {
    id: com_edit_multiline
    Item {
      anchors.fill: parent
      ScrollView {
        id: item_scroll
        clip: true
        anchors.fill: parent
        ScrollBar.vertical: FluScrollBar {
          parent: item_scroll
          x: item_scroll.mirrored ? 0 : item_scroll.width - width
          y: item_scroll.topPadding
          height: item_scroll.availableHeight
          active: item_scroll.ScrollBar.horizontal.active
        }
        FluMultilineTextBox {
          id: text_box
          text: display
          readOnly: true === columnSource[column].readOnly
          verticalAlignment: TextInput.AlignVCenter
          Component.onCompleted: {
            forceActiveFocus()
            selectAll()
          }
          rightPadding: 24
          onCommit: {
            if (!readOnly) {
              display = text
            }
            cellUpdated(row, column, text)
            tableView.closeEditor()
          }
        }
      }
      FluIconButton {
        iconSource: FluentIcons.ChromeClose
        iconSize: 10
        width: 20
        height: 20
        visible: {
          if (text_box.readOnly)
            return false
          return text_box.text !== ""
        }
        anchors {
          verticalCenter: parent.verticalCenter
          right: parent.right
          rightMargin: 5
        }
        onClicked: {
          text_box.text = ""
        }
      }
    }
  }
  Component {
    id: com_text
    FluText {
      id: item_text
      text: modelData
      elide: Text.ElideRight
      wrapMode: Text.WrapAnywhere
      anchors {
        fill: parent
        leftMargin: 11
        rightMargin: 11
        topMargin: 6
        bottomMargin: 6
      }
      verticalAlignment: Text.AlignVCenter
      MouseArea {
        acceptedButtons: Qt.NoButton
        id: hover_handler
        hoverEnabled: true
        anchors.fill: parent
      }
      FluTooltip {
        text: item_text.text
        delay: 500
        visible: item_text.contentWidth < item_text.implicitWidth && item_text.contentHeight < item_text.implicitHeight && hover_handler.containsMouse
      }
    }
  }

  MouseArea {
    id: scroll_table
    hoverEnabled: true
    anchors.left: header_vertical.right
    anchors.top: header_horizontal.bottom
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    onExited: {
      d.rowHoverIndex = -1
    }
    onCanceled: {
      d.rowHoverIndex = -1
    }
    ScrollView {
      anchors.fill: parent
      ScrollBar.horizontal.policy: ScrollBar.AsNeeded
      ScrollBar.vertical.policy: ScrollBar.AsNeeded
      TableView {
        id: table_view
        ListModel {
          id: model_columns
        }
        boundsBehavior: Flickable.StopAtBounds
        ScrollBar.horizontal: FluScrollBar {
          id: scroll_bar_h
        }
        ScrollBar.vertical: FluScrollBar {
          id: scroll_bar_v
        }
        columnWidthProvider: function (column) {
          var w = columnSource[column].width
          if (!w) {
            w = columnSource[column].minimumWidth
          }
          if (!w) {
            w = d.defaultItemWidth
          }
          if (item_loader_layout.cellItem) {
            if (column === item_loader.column) {
              item_loader_layout.width = w
            }
            if (column === item_loader.column - 1) {
              let cellPosition = item_loader_layout.cellItem.mapToItem(scroll_table, 0, 0)
              item_loader_layout.x = table_view.contentX + cellPosition.x
            }
          }
          return w
        }
        rowHeightProvider: function (row) {
          if (row >= table_model.rowCount) {
            return 0
          }
          var h = table_model.getRow(row).height
          if (!h) {
            h = table_model.getRow(row).minimumHeight
          }
          if (!h) {
            h = d.defaultItemHeight
          }
          if (item_loader_layout.cellItem) {
            if (row === item_loader.row) {
              item_loader_layout.height = h
            }
            if (row === item_loader.row - 1) {
              let cellPosition = item_loader_layout.cellItem.mapToItem(scroll_table, 0, 0)
              item_loader_layout.y = table_view.contentY + cellPosition.y
            }
          }
          return h
        }
        model: table_model
        clip: true
        delegate: MouseArea {
          hoverEnabled: true
          implicitHeight: 40
          implicitWidth: {
            var w = columnSource[column].width
            if (!w) {
              w = columnSource[column].minimumWidth
            }
            if (!w) {
              w = d.defaultItemWidth
            }
            return w
          }
          onEntered: {
            d.rowHoverIndex = row
          }
          Rectangle {
            id: item_table
            anchors.fill: parent
            property point position: Qt.point(column, row)
            color: {
              if (d.rowHoverIndex === row || d.currentRow === table_model.getRow(row).__index) {
                return FluTheme.dark ? Qt.rgba(1, 1, 1, 0.06) : Qt.rgba(0, 0, 0, 0.06)
              }
              return (row % 2 !== 0) ? control.color : (FluTheme.dark ? Qt.rgba(1, 1, 1, 0.015) : Qt.rgba(0, 0, 0, 0.015))
            }
            Rectangle {
              height: 18
              radius: 1.5
              color: FluTheme.primaryColor
              width: 3
              visible: d.currentRow === table_model.getRow(row).__index && column === 0
              anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: 3
              }
            }
            MouseArea {
              anchors.fill: parent
              acceptedButtons: Qt.LeftButton
              onPressed: {
                closeEditor()
              }
              onCanceled: {
              }
              onReleased: {
              }
              onDoubleClicked: {
                if (typeof (display) == "object") {
                  return
                }
                item_loader.sourceComponent = d.obtEditDelegate(column, row, item_table)
                d.isEditing = true
              }
              onClicked:
                  (event) => {
                d.currentRow = table_model.getRow(row).__index
                item_loader.sourceComponent = undefined
                event.accepted = true
              }
            }
            FluLoader {
              property var itemModel: model
              property var modelData: display
              property var tableView: table_view
              property var tableModel: table_model
              property var position: item_table.position
              property int row: position.y
              property int column: position.x
              property var currentItem: table_model.getRow(row)
              property var currentProperty: columnSource[column]
              property var currentValue: currentItem[currentProperty.dataIndex]

              property var options: {
                if (typeof (modelData) == "object") {
                  return modelData.options
                }
                return {}
              }
              anchors.fill: parent
              sourceComponent: {
                if (typeof (modelData) == "object") {
                  return modelData.comId
                }
                const type = columnSource[column].type
                if (typeof(type) === 'string' && type.startsWith("Builtin.")) {
                  if (columnSource[column].extra) {
                    return com_conv
                  }
                  return com_loading
                }
                if (type === 'enum') {
                  return com_combo
                }
                return com_text
              }
            }
          }
        }
      }
      MouseArea {
        property var cellItem
        id: item_loader_layout
        acceptedButtons: Qt.NoButton
        visible: item_loader.sourceComponent
        onVisibleChanged: {
          if (!visible) {
            item_loader_layout.cellItem = undefined
          }
        }
        hoverEnabled: true
        z: 2
        onEntered: {
          d.rowHoverIndex = -1
        }
        FluLoader {
          id: item_loader
          property var display
          property var currentItem
          property var currentProperty
          property int column
          property int row
          property var tableView: control
          sourceComponent: undefined
          anchors.fill: parent
          onDisplayChanged: {
            var obj = table_model.getRow(row)
            obj[columnSource[column].dataIndex] = display
            table_model.setRow(row, obj)
          }
        }
      }
    }
  }
  Component {
    id: com_handle
    Item {
    }
  }
  Component {
    id: com_column_text
    FluText {
      id: column_text
      text: modelData
      anchors.fill: parent
      horizontalAlignment: Text.AlignHCenter
      verticalAlignment: Text.AlignVCenter
    }
  }

  TableView {
    id: header_horizontal
    model: TableModel {
      id: header_model
      rows: d.header_rows
    }
    syncDirection: Qt.Horizontal
    anchors.left: scroll_table.left
    anchors.top: parent.top
    implicitWidth: syncView ? syncView.width : 0
    implicitHeight: Math.max(1, contentHeight)
    syncView: table_view
    boundsBehavior: Flickable.StopAtBounds
    clip: true
    delegate: Rectangle {
      id: column_item_control
      readonly property real cellPadding: 8
      property bool canceled: false
      property int columnIndex: column
      readonly property var obj: columnSource[column]
      implicitWidth: {
        return (item_column_loader.item && item_column_loader.item.implicitWidth) + (cellPadding * 2)
      }
      implicitHeight: Math.max(36, (item_column_loader.item && item_column_loader.item.implicitHeight) + (cellPadding * 2))
      color: FluTheme.dark ? Qt.rgba(50 / 255, 50 / 255, 50 / 255, 1) : Qt.rgba(247 / 255, 247 / 255, 247 / 255, 1)
      Rectangle {
        border.color: control.borderColor
        width: parent.width
        height: 1
        anchors.top: parent.top
        color: "#00000000"
        radius: control.radius
      }
      Rectangle {
        border.color: control.borderColor
        width: parent.width
        height: 1
        anchors.bottom: parent.bottom
        color: "#00000000"
        radius: control.radius
      }
      Rectangle {
        border.color: control.borderColor
        width: 1
        height: parent.height
        anchors.left: parent.left
        color: "#00000000"
        radius: control.radius
      }
      Rectangle {
        border.color: control.borderColor
        width: 1
        height: parent.height
        anchors.right: parent.right
        color: "#00000000"
        visible: column === tableModel.columnCount - 1
        radius: control.radius
      }
      MouseArea {
        id: column_item_control_mouse
        anchors.fill: parent
        anchors.rightMargin: 6
        hoverEnabled: true
        onCanceled: {
          column_item_control.canceled = true
        }
        onContainsMouseChanged: {
          if (!containsMouse) {
            column_item_control.canceled = false
          }
        }
        onClicked: (event) => {
          closeEditor()
        }
      }
      FluLoader {
        id: item_column_loader
        property var itemModel: model
        property var modelData: model.display
        property var tableView: table_view
        property var tableModel: table_model
        property var options: {
          if (typeof (modelData) == "object") {
            return modelData.options
          }
          return {}
        }
        property int column: column_item_control.columnIndex
        width: parent.width
        height: parent.height
        sourceComponent: {
          if (typeof (modelData) == "object") {
            return modelData.comId
          }
          return com_column_text
        }
      }
      MouseArea {
        property point clickPos: "0,0"
        height: parent.height
        width: 6
        anchors.right: parent.right
        acceptedButtons: Qt.LeftButton
        hoverEnabled: true
        visible: !(obj.width === obj.minimumWidth && obj.width === obj.maximumWidth && obj.width)
        cursorShape: Qt.SplitHCursor
        onPressed:
            (mouse) => {
          header_horizontal.interactive = false
          FluTools.setOverrideCursor(Qt.SplitHCursor)
          clickPos = Qt.point(mouse.x, mouse.y)
        }
        onReleased: {
          header_horizontal.interactive = true
          FluTools.restoreOverrideCursor()
        }
        onCanceled: {
          header_horizontal.interactive = true
          FluTools.restoreOverrideCursor()
        }
        onPositionChanged:
            (mouse) => {
          if (!pressed) {
            return
          }
          var delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y)
          var minimumWidth = obj.minimumWidth
          var maximumWidth = obj.maximumWidth
          var w = obj.width
          if (!w) {
            w = d.defaultItemWidth
          }
          if (!minimumWidth) {
            minimumWidth = d.defaultItemWidth
          }
          if (!maximumWidth) {
            maximumWidth = 65535
          }
          obj.width = Math.min(Math.max(minimumWidth, w + delta.x), maximumWidth)
          table_view.forceLayout()
        }
      }
    }
  }
  TableView {
    id: header_vertical
    boundsBehavior: Flickable.StopAtBounds
    anchors.top: scroll_table.top
    anchors.left: parent.left
    implicitWidth: Math.max(1, contentWidth)
    implicitHeight: syncView ? syncView.height : 0
    syncDirection: Qt.Vertical
    syncView: table_view
    clip: true
    model: TableModel {
      FTableModelColumn {
      }
      rows: {
        if (dataSource)
          return dataSource
        return []
      }
    }
    onContentYChanged: {
      timer_force_layout.restart()
    }
    Timer {
      interval: 50
      id: timer_force_layout
      onTriggered: {
        header_vertical.forceLayout()
      }
    }
    delegate: Rectangle {
      id: item_control
      readonly property real cellPadding: 8
      property bool canceled: false
      implicitWidth: Math.max(30, row_text.implicitWidth + (cellPadding * 2))
      implicitHeight: row_text.implicitHeight + (cellPadding * 2)
      width: implicitWidth
      height: implicitHeight
      color: FluTheme.dark ? Qt.rgba(50 / 255, 50 / 255, 50 / 255, 1) : Qt.rgba(247 / 255, 247 / 255, 247 / 255, 1)
      Rectangle {
        border.color: control.borderColor
        width: parent.width
        height: 1
        anchors.top: parent.top
        color: "#00000000"
        radius: control.radius
      }
      Rectangle {
        border.color: control.borderColor
        width: parent.width
        height: 1
        anchors.bottom: parent.bottom
        visible: row === tableModel.rowCount - 1
        color: "#00000000"
        radius: control.radius
      }
      Rectangle {
        border.color: control.borderColor
        width: 1
        height: parent.height
        anchors.left: parent.left
        color: "#00000000"
        radius: control.radius
      }
      Rectangle {
        border.color: control.borderColor
        width: 1
        height: parent.height
        anchors.right: parent.right
        color: "#00000000"
        radius: control.radius
      }
      FluText {
        id: row_text
        anchors.centerIn: parent
        text: row + 1
      }
      MouseArea {
        id: item_control_mouse
        anchors.fill: parent
        anchors.bottomMargin: 6
        hoverEnabled: true
        onCanceled: {
          item_control.canceled = true
        }
        onContainsMouseChanged: {
          if (!containsMouse) {
            item_control.canceled = false
          }
        }
        onClicked:
            (event) => {
          closeEditor()
        }
      }
      MouseArea {
        property point clickPos: "0,0"
        height: 6
        width: parent.width
        anchors.bottom: parent.bottom
        acceptedButtons: Qt.LeftButton
        cursorShape: Qt.SplitVCursor
        visible: {
          var obj = table_model.getRow(row)
          return !(obj.height === obj.minimumHeight && obj.height === obj.maximumHeight && obj.height)
        }
        onPressed:
            (mouse) => {
          header_vertical.interactive = false
          FluTools.setOverrideCursor(Qt.SplitVCursor)
          clickPos = Qt.point(mouse.x, mouse.y)
        }
        onReleased: {
          header_vertical.interactive = true
          FluTools.restoreOverrideCursor()
        }
        onCanceled: {
          header_vertical.interactive = true
          FluTools.restoreOverrideCursor()
        }
        onPositionChanged:
            (mouse) => {
          if (!pressed) {
            return
          }
          var obj = table_model.getRow(row)
          var delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y)
          var minimumHeight = obj.minimumHeight
          var maximumHeight = obj.maximumHeight
          var h = obj.height
          if (!h) {
            h = d.defaultItemHeight
          }
          if (!minimumHeight) {
            minimumHeight = d.defaultItemHeight
          }
          if (!maximumHeight) {
            maximumHeight = 65535
          }
          obj.height = Math.min(Math.max(minimumHeight, h + delta.y), maximumHeight)
          table_model.setRow(row, obj)
          table_view.forceLayout()
        }
      }
    }
  }

  function closeEditor() {
    d.isEditing = false
    item_loader.sourceComponent = null
  }

  function editing() {
    return d.isEditing
  }

  function resetPosition() {
    scroll_bar_h.position = 0
    scroll_bar_v.position = 0
  }

  function customItem(comId, options = {}) {
    var o = {}
    o.comId = comId
    o.options = options
    return o
  }

  function updateRow(row, obj) {
    table_model.setRow(row, obj)
  }

  function sort(order) {
    let sortedArray = []
    for (var i = 0; i < table_model.rowCount; i++) {
      let row = table_model.getRow(i)
      sortedArray.push(row)
    }
    if (order === undefined) {
      sortedArray.sort((a, b) => a.__index - b.__index)
    } else {
      sortedArray.sort(order)
    }
    table_model.clear()
    table_model.rows = sortedArray
  }
}
