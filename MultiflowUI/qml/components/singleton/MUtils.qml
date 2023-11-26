pragma Singleton

import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

Item {
    Timer {
        id: timer
    }

    function isNumeric(str) {
        if (typeof str != "string") {
            return false
        }
        return !isNaN(str) && !isNaN(parseFloat(str))
    }

    function setTimeout(functionRef, delayTime) {
        timer.interval = delayTime;
        timer.repeat = false;
        timer.triggered.connect(functionRef);
        timer.start();
    }

    /**
     * @param 防止associationValue出现在keys中
     */
    function wrapMEntityKeys(keys) {
        return keys.filter(k => k !== "associateValue")
    }
}
