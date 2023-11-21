import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Multiflow.UI
import FluentUI

TextArea {
  property color textColor: FluTheme.dark ? FluColors.White : FluColors.Grey220
  id: control
  Layout.fillWidth: true
  font.family: "Consolas"
  font.weight: Font.DemiBold
  color: textColor
  readOnly: true
  activeFocusOnTab: false
  activeFocusOnPress: false
  renderType: FluTheme.nativeText ? Text.NativeRendering : Text.QtRendering
  padding: 0
  leftPadding: 0
  rightPadding: 0
  topPadding: 0
  selectByMouse: true
  selectedTextColor: color
  bottomPadding: 0
  selectionColor: FluTools.colorAlpha(FluTheme.primaryColor, 0.5)
  onSelectedTextChanged: {
    control.forceActiveFocus()
  }
  MouseArea {
    anchors.fill: parent
    cursorShape: Qt.IBeamCursor
    acceptedButtons: Qt.RightButton
    onClicked: control.echoMode !== TextInput.Password && menu.popup()
  }
  MouseArea {
    anchors.fill: parent
    cursorShape: Qt.IBeamCursor
    onClicked: control.selectAll()
  }
  FluTextBoxMenu {
    id: menu
    inputItem: control
  }
}

