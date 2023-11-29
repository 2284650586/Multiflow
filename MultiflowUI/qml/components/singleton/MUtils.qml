pragma Singleton

import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

Item {
    property var fontFamily: FluTools.isMacos()
        ? "PingFang SC"
        : "Microsoft YaHei"

    function isNumeric(str) {
        if (typeof str != "string") {
            return false
        }
        return !isNaN(str) && !isNaN(parseFloat(str))
    }

    /**
     * @param 防止associationValue出现在keys中
     */
    function wrapMEntityKeys(keys) {
        return keys.filter(k => k !== "associateValue")
    }

    function reversed(array) {
        return array.slice().reverse()
    }
}
