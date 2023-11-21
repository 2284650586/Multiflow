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

        Component.onCompleted: {
          well.keys().forEach(key => {
            _addTab(well[key].name, tab, {entity: well[key].value});
          })
        }
      }

      // Background
      Rectangle {
        anchors.fill: parent
        color: "transparent"
        radius: 8
      }
    }
  }

  Component {
    id: tab

    TabContent {
      property int maxTextFieldWidth: 0

      Repeater {
        id: repeater
        model: argument.entity.keys()

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
                  comboBoxEnum.currentIndex = entity.value ? items.indexOf(entity.value) : 0;
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

      FluFilledButton {
        text: "完成"
        Layout.margins: 10

        onClicked: {
          notifyDataChange()
          window.close()
        }
      }
    } // TabContent
  } // Component

  component TabContent: Item {
    default property alias content: contentView.data

    id: tabContent
    anchors.fill: parent
    anchors.margins: 10

    ColumnLayout {
      id: contentView
    }
  }

  function _addTab(title, control, args) {
    tabView.appendTab("qrc:/resources/image/linepointer.png", title, control, Object.assign({
      "title": title
    }, args));
  }

  function notifyDataChange() {
    onDataChanged(well)
  }

  function _isNumeric(str) {
    if (typeof str != "string") {
      return false
    }
    return !isNaN(str) && !isNaN(parseFloat(str))
  }
}
