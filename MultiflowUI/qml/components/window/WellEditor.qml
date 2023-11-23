import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Multiflow.UI
import FluentUI
import Qt.labs.qmlmodels
import "qrc:/qml/components/widget/"
import "qrc:/qml/components/singleton/"

FluWindow {
  id: window
  objectName: "wellEditor"
  width: 800
  height: 600
  title: "管井数据"
  visible: true

  signal onDataChanged(var data)

  property var well: entity

  Component.onCompleted: {
    /**
     * `well`: 管井数据
     * `well.general`: general项
     * `well.general.name`: general项的名字：“基本信息”
     * `well.general.value`: general项的数据
     * `well.general.value.name`: general项中的name项
     * `well.general.value.name.value`: general项中的name项的值：管井实际名称
     */
    window.title += ` - ${well.general.value.name.value}`
    onDataChanged.connect(bridge.onDataChanged)
  }

  FluArea {
    anchors.fill: parent
    anchors.margins: 10
    border.color: Colors.border
    color: Colors.background
    radius: 8
    clip: true

    FluTabView {
      id: tabView

      addButtonVisibility: FluTabViewType.Nerver
      closeButtonVisibility: FluTabViewType.Nerver
      anchors.fill: parent

      Component.onCompleted: {
        well.keys().forEach(key => {
          _addTab(well[key].name, tab, {category: key, entity: well[key].value})
        })
      }
    }
  }
  FluContentDialog {
    property string dialogTitle
    property string dialogMessage

    id: dialog
    title: dialogTitle
    message: dialogMessage
    buttonFlags: FluContentDialogType.NeutralButton
    neutralText: "好"
  }

  Component {
    id: tab

    TabContent {
      property int maxTextFieldWidth: 0

      anchors.fill: parent
      Layout.fillHeight: true
      Layout.fillWidth: true

      ColumnLayout {
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.margins: 10

        // 表单区域
        Repeater {
          id: repeater
          model: getKeys(argument.entity)

          RowLayout {
            property var key: modelData
            property var entity: argument.entity[key]
            property FluText label: label

            spacing: 8
            Layout.fillWidth: true

            FluText {
              id: label
              Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
              font.pointSize: 11
              font.weight: Font.DemiBold

              Component.onCompleted: {
                label.text = `${entity.name}: `
              }
            }

            Loader {
              id: contentView
              Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
              Layout.preferredWidth: 200
              sourceComponent: _getComponentId(entity)

              Component {
                id: componentTextField

                FluTextBox {
                  id: textBoxString
                  onTextChanged: {
                    entity.value = text
                  }

                  Component.onCompleted: {
                    textBoxString.text = entity.value
                  }
                }
              }

              Component {
                id: componentEnum

                FluComboBox {
                  property var items: entity.extra.split(", ")

                  id: comboBoxEnum
                  model: items
                  currentIndex: -1
                  onCurrentTextChanged: {
                    entity.value = currentText
                  }

                  Component.onCompleted: {
                    comboBoxEnum.currentIndex = entity.value ? items.indexOf(entity.value) : 0
                  }
                }
              }

              Component {
                id: componentConverter

                RowLayout {
                  property var units: entity.extra.units()

                  FluTextBox {
                    id: textBox
                    Layout.preferredWidth: 120
                    onTextChanged: {
                      entity.value = text
                    }
                    Component.onCompleted: {
                      textBox.text = entity.value
                    }
                  }

                  FluComboBox {
                    property var lastUnit: entity.associateValue ? units[entity.associateValue] : units[0]

                    id: comboBox
                    model: units
                    Layout.preferredWidth: 80
                    onCurrentTextChanged: {
                      if (!_isNumeric(textBox.text)) {
                        return
                      }
                      let oldValue = parseFloat(textBox.text)
                      let newUnit = currentText
                      let newValue = entity.extra.convert(oldValue, lastUnit, newUnit)
                      newValue = Number(newValue.toFixed(2))
                      textBox.text = `${newValue}`
                      entity.associateValue = currentIndex
                      lastUnit = currentText
                    }

                    Component.onCompleted: {
                      comboBox.currentIndex = entity.associateValue ? entity.associateValue : 0
                    }
                  }
                }
              }

              function _getComponentId(entity) {
                if (entity.type.startsWith("Builtin.")) {
                  return componentConverter
                }
                switch (entity.type) {
                  case "string":
                    return componentTextField

                  case "enum":
                    return componentEnum

                  default:
                    return componentTextField
                }
              }
            }

            FluText {
              Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
              text: `(${key})`
              color: "gray"
            }
          } // Row
        } // Repeater
      }

      // VSpacer
      Item {
        Layout.fillHeight: true
        Layout.fillWidth: true
      }

      // 好！表格区域！
      Loader {
        id: loaderTableArea

        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.margins: 10

        // High frequency keys
        property var keys: getHighFrequencyKeys(argument.entity)
        property var dataSource: []

        Component {
          id: componentTableArea

          FluArea {
            id: hfArea
            visible: keys.length > 0
            radius: 8
            clip: true

            FTableView {
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
                      independentVariables.remove(argument.category, row)
                    }
                  }
                }
              }

              function getColumnSource() {
                const columns = []
                for (const key of loaderTableArea.keys) {
                  const property = argument.entity[key]
                  columns.push({
                    title: property.name,
                    dataIndex: key,
                    minimumWidth: 100,
                    maximumWidth: 300,
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
                const size = independentVariables.size(argument.category)
                for (let i = 0; i < size; ++i) {
                  const row = {}
                  for (const key of loaderTableArea.keys) {
                    row[key] = independentVariables.get(argument.category, i, key) || '0'
                  }
                  row['action'] = tableView.customItem(componentActionArea)
                  rows.push(row)
                }
                return rows
              }

              function refreshData() {
                dataSource = readFromIv()
                tableView.dataSource = dataSource
              }
            }

            Component.onCompleted: {
              tableView.refreshData()
              tableView.cellUpdated.connect((row, column, value) => {
                const key = loaderTableArea.keys[column]
                independentVariables.set(argument.category, row, key, value)
                console.log(`Setting iv[${argument.category}][${row}][${key}] = ${value}`)
              })
              independentVariables.sizeChanged.connect((category) => {
                if (category !== argument.category) {
                  return
                }
                tableView.refreshData()
              })
            }
          } // FluArea
        }

        sourceComponent: keys.length > 0 ? componentTableArea : null
      }

      RowLayout {
        Layout.margins: 10
        Layout.fillWidth: true

        FluButton {
          visible: loaderTableArea.keys.length > 0
          text: "添加一组数据"
          Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
          onClicked: {
            independentVariables.createEmpty(argument.category)
          }
        }

        HSpacer {
        }

        FluFilledButton {
          visible: loaderTableArea.keys.length > 0
          text: "计算"
          Layout.alignment: Qt.AlignRight | Qt.AlignBottom
          onClicked: {
            _handleCalculation(argument.category)
          }
        }

        FluButton {
          text: "保存"
          Layout.alignment: Qt.AlignRight | Qt.AlignBottom
          onClicked: {
            notifyDataChange()
            window.close()
          }
        }
      }

      Component.onCompleted: {
        _updateMaxWidth(repeater, 'label')
      }

      // Update max width programmatically
      function _updateMaxWidth(repeater, itemId) {
        let maxWidth = 0
        for (let i = 0; i < repeater.count; ++i) {
          let item = repeater.itemAt(i)[itemId]
          maxWidth = Math.max(maxWidth, item.paintedWidth)
        }
        for (let i = 0; i < repeater.count; ++i) {
          let item = repeater.itemAt(i)[itemId]
          item.Layout.preferredWidth = maxWidth
        }
      }

      function _handleCalculation(category) {
        if (independentVariables.size(category) === 0) {
          showAlert("无法计算", "请添加至少一组数据")
          return
        }
        calculationUnit.update(argument.entity, independentVariables)
        const results = calculationUnit.evaluate(category)
        console.log(results)
        showAlert("计算结果", results.join(", "))
      }
    } // TabContent
  } // Component

  component TabContent: Item {
    default property alias content: contentView.data

    id: tabContent
    anchors.margins: 10

    ColumnLayout {
      id: contentView
      anchors.fill: parent
    }
  }

  function _addTab(title, control, args) {
    tabView.appendTab("qrc:/resources/image/linepointer.png", title, control, Object.assign({
      "title": title
    }, args))
  }

  function notifyDataChange() {
    onDataChanged(well)
  }

  function getKeys(entity) {
    return entity.keys().filter(k => !entity[k].isHighFrequency)
  }

  function getHighFrequencyKeys(entity) {
    return entity.keys().filter(k => entity[k].isHighFrequency)
  }

  function showAlert(title, message) {
    dialog.dialogTitle = title
    dialog.dialogMessage = message
    dialog.open()
  }

  function _isNumeric(str) {
    if (typeof str != "string") {
      return false
    }
    return !isNaN(str) && !isNaN(parseFloat(str))
  }
}
