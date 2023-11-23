pragma Singleton

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import FluentUI

QtObject {
  property var background: FluTheme.dark
    ? Qt.rgba(39 / 255, 39 / 255, 39 / 255, 1)
    : Qt.rgba(251 / 255, 251 / 255, 253 / 255, 1)

  property var border: FluTheme.dark
    ? Qt.rgba(45 / 255, 45 / 255, 45 / 255, 1)
    : Qt.rgba(226 / 255, 229 / 255, 234 / 255, 1)

  property var areaBorder: FluTheme.dark
    ? Qt.rgba(55 / 255, 55 / 255, 55 / 255, 1)
    : Qt.rgba(226 / 255, 229 / 255, 234 / 255, 1)

  property var white: Qt.rgba(255 / 255, 255 / 255, 255 / 255, 1)
}
