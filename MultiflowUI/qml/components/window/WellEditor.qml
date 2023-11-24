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
  width: 800
  height: 600
  title: "管井数据"
  visible: true

  signal onDataChanged(var data)

  property var well: entity

  Component.onCompleted: {
    window.title += ` - ${well.general.value.name.value}`
    onDataChanged.connect(bridge.onDataChanged)
  }

  Item {
    id: d

    property var categoryToKeys: ({})
    property var categoryToHfKeys: ({})

    Component.onCompleted: {
      init()
    }
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
          const argument = {category: key, entity: well[key].value}
          initPage(argument)
          addTab(well[key].name, tab, argument)
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

        Repeater {
          id: repeater
          model: d.categoryToKeys[argument.category]

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
                  property var didInitliazed: false
                  property var items: entity.extra.split(", ")

                  id: comboBoxEnum
                  model: items
                  currentIndex: -1
                  onCurrentTextChanged: {
                    entity.value = currentText
                    notifyDataChange()
                    if (didInitliazed) {
                      initPage(argument)
                      repeater.reload()
                      entity.value = currentText
                      reloadTable()
                    }
                  }
                  Component.onCompleted: {
                    comboBoxEnum.currentIndex = entity.value ? items.indexOf(entity.value) : 0
                    didInitliazed = true
                  }
                }
              }

              Component {
                id: componentConverter

                RowLayout {
                  property var units: entity.extra.units()
                  spacing: 0

                  FluTextBox {
                    id: textBox
                    Layout.preferredWidth: 125
                    Layout.fillHeight: true
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
                    Layout.preferredWidth: 75
                    Layout.fillHeight: true
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

          function reload() {
            repeater.model = d.categoryToKeys[argument.category]
            rearrange()
          }

          function rearrange() {
            updateMaxWidth(repeater, repeater.model.length, 'label')
          }

          Component.onCompleted: {
            rearrange()
          }
        } // Repeater
      }

      // VSpacer
      Item {
        Layout.fillHeight: true
        Layout.fillWidth: true
      }

      Component {
        id: componentTableArea

        FluArea {
          //! property var keys: d.categoryToHfKeys[argument.category]
          //! property var dataSource: []

          id: hfArea
          visible: d.categoryToHfKeys[argument.category].length > 0
          radius: 8
          clip: true
          Layout.fillWidth: true
          Layout.fillHeight: true
          Layout.margins: 10

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
                    notifyDataChange()
                  }
                }
              }
            }

            function getColumnSource() {
              const columns = []
              for (const key of d.categoryToHfKeys[argument.category]) {
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
              const size = independentVariables.size(argument.category)
              for (let i = 0; i < size; ++i) {
                const row = {}
                for (const key of getAllHfKeys(argument)) {
                  row[key] = independentVariables.get(argument.category, i, key) || '0'
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

          Component.onCompleted: {
            tableView.refreshData()
            tableView.cellUpdated.connect((row, column, value) => {
              const key = d.categoryToHfKeys[argument.category][column]
              independentVariables.set(argument.category, row, key, value)
              // console.log(`SET: iv[${argument.category}][${row}][${key}] = "${value}"`)
              notifyDataChange()
            })
            independentVariables.sizeChanged.connect((category) => {
              if (category !== argument.category) {
                return
              }
              tableView.refreshData()
            })
          }

          function getTableView() {
            return tableView
          }
        } // FluArea
      }

      // 好！表格区域！
      Loader {
        id: tableLoader
        Layout.fillWidth: true
        Layout.fillHeight: true
        sourceComponent: d.categoryToHfKeys[argument.category].length > 0 ? componentTableArea : null
      }

      RowLayout {
        Layout.margins: 10
        Layout.fillWidth: true

        FluButton {
          visible: d.categoryToHfKeys[argument.category].length > 0
          text: "添加一组数据"
          Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
          onClicked: {
            independentVariables.createEmpty(argument.category)
          }
        }

        HSpacer {
        }

        FluFilledButton {
          visible: d.categoryToHfKeys[argument.category].length > 0
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

      function _handleCalculation(category) {
        if (independentVariables.size(category) === 0) {
          showAlert("无法计算", "请添加至少一组数据")
          return
        }
        calculationUnit.update(argument.entity, independentVariables)
        const results = calculationUnit.evaluate(category)
        showAlert("计算结果", results.join(", "))
      }

      Component {
        id: tableModelComponent
        TableModel {
        }
      }

      function reloadTable() {
        const hfArea = tableLoader.item
        if (hfArea) {
          d.categoryToHfKeys[argument.category] = getHighFrequencyKeys(argument)
          const tableView = hfArea.getTableView()
          const globalD = tableView.getGlobal()
          tableView.columnSource = tableView.getColumnSource()
        }
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

  // Update max width programmatically
  function updateMaxWidth(repeater, count, itemId) {
    let maxWidth = 0
    for (let i = 0; i < count; ++i) {
      if (!repeater.itemAt(i)) {
        return
      }
      let item = repeater.itemAt(i)[itemId]
      maxWidth = Math.max(maxWidth, item.paintedWidth)
    }
    for (let i = 0; i < count; ++i) {
      let item = repeater.itemAt(i)[itemId]
      item.Layout.preferredWidth = maxWidth
    }
  }

  function addTab(title, control, args) {
    tabView.appendTab("qrc:/resources/image/linepointer.png", title, control, Object.assign({
      "title": title
    }, args))
  }

  function init() {
    console.log("init")
  }

  function initPage(argument) {
    d.categoryToKeys[argument.category] = getKeys(argument)
    d.categoryToHfKeys[argument.category] = getHighFrequencyKeys(argument)
  }

  function notifyDataChange() {
    onDataChanged(well)
  }

  function getKeys(argument) {
    return argument.entity.keys().filter(
        k => !argument.entity[k].isHighFrequency
        && argument.entity[k].shouldEnable(argument.entity)
    )
  }

  function getAllHfKeys(argument) {
    return argument.entity.keys().filter(
        k => argument.entity[k].isHighFrequency
    )
  }

  function getHighFrequencyKeys(argument) {
    return argument.entity.keys().filter(
        k => argument.entity[k].isHighFrequency
        && argument.entity[k].shouldEnable(argument.entity)
    )
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
