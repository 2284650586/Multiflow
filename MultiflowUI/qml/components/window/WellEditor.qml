import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Multiflow.UI
import FluentUI
import "qrc:/qml/components/widget/"
import "qrc:/qml/components/singleton/"

FluWindow {
  id: window
  objectName: "wellEditor"
  width: 1000
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

  RowLayout {
    anchors.fill: parent
    anchors.margins: 10

    Rectangle {
      Layout.fillHeight: true
      color: "darkgray"
      radius: 8
      width: 300
    }

    FluArea {
      Layout.fillHeight: true
      Layout.fillWidth: true
      border.color: Colors.border
      color: Colors.background
      radius: 8

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

      Repeater {
        id: repeater
        model: getProperties(argument.entity)

        RowLayout {
          property var id: modelData
          property var entity: argument.entity[id]
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
            text: `(${id})`
            color: "gray"
          }
        } // Row
      } // Repeater


      // VSpacer
      Item {
        Layout.fillHeight: true
        Layout.fillWidth: true
      }

      FluArea {
        property var properties: getHighFrequencyProperties(argument.entity)

        visible: properties.length > 0
        id: hfArea
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.margins: 10
        radius: 8

        ColumnLayout {
          anchors.fill: parent
          anchors.margins: 15
          Layout.fillHeight: true
          Layout.fillWidth: true

          // 表头
          RowLayout {
            spacing: 0
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop

            Repeater {
              model: hfArea.properties

              RowLayout {
                id: row
                Layout.preferredWidth: 150
                property var property: argument.entity[modelData]
                property var isLastItem: index === hfArea.properties.length - 1

                FluText {
                  Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                  text: row.property.name
                  font.pointSize: 11
                  font.weight: Font.DemiBold
                }

                FluText {
                  text: "|"
                  color: "gray"
                  horizontalAlignment: Text.AlignHCenter
                  visible: !isLastItem
                }
              }
            } // Repeater
          } // RowLayout 表头

          Repeater {
            id: repeaterIndependentVariables
            model: independentVariables.size(argument.category)

            RowLayout {
              property var ivIndex: index

              spacing: 0
              Layout.fillWidth: true
              Layout.alignment: Qt.AlignLeft | Qt.AlignTop

              Repeater {
                model: hfArea.properties

                RowLayout {
                  property var key: modelData

                  id: row
                  Layout.preferredWidth: 150

                  FluTextBox {
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    onTextChanged: {
                      independentVariables.set(argument.category, ivIndex, key, text)
                    }

                    Component.onCompleted: {
                      text = independentVariables.get(argument.category, ivIndex, key)
                    }
                  }
                }
              } // Repeater
            }
          }

          Component.onCompleted: {
            independentVariables.sizeChanged.connect((category) => {
              if (category !== argument.category) {
                return
              }
              repeaterIndependentVariables.model = independentVariables.size(category)
            })
          }

          FluButton {
            text: "添加"
            Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
            Layout.margins: 10
            onClicked: {
              independentVariables.createEmpty(argument.category)
            }
          }
        } // ColumnLayout
      } // FluArea

      RowLayout {
        Layout.margins: 10
        Layout.alignment: Qt.AlignRight | Qt.AlignBottom

        FluFilledButton {
          text: "演算"
          onClicked: {
            _handleCalculation()
          }
        }

        FluButton {
          text: "完成"
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

      function _handleCalculation() {
        calculationUnit.update(argument.entity, independentVariables)
        const results = calculationUnit.evaluate("reservoir")
        console.log(results)
        showAlert("演算结果", results.join(", "))
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

  function getProperties(entity) {
    return entity.keys().filter(k => !entity[k].isHighFrequency)
  }

  function getHighFrequencyProperties(entity) {
    return entity.keys().filter(k => entity[k].isHighFrequency)
  }

  function getColumnSource(properties) {
    return properties.map(p => {
      // 哎呀这箭头函数突然就不灵了
      return {
        title: p.name,
        dataIndex: p.id,
      }
    })
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
