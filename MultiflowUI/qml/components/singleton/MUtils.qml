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


    function ivValueAtUnit(iv, root, category, index, key, toUnit = null) {
        const value = iv.get(category, index, key)
        return valueAtUnit(root, category, key, value, toUnit)
    }

    function valueAtUnit(root, category, key, value, toUnit = null) {
        if (!root[category]) {
            console.error(`[Converter] category (${category}) not found`)
            return value
        }
        const entity = root[category].value
        const converter = entity[key].extra
        const units = converter.units()
        const savedUnitIndex = entity[key].associateValue
        const preferredUnit = entity[key].preferredUnit
        const fromUnit = !savedUnitIndex
            ? (preferredUnit || units[0])
            : units[savedUnitIndex]
        const desiredUnit = toUnit || preferredUnit
        const result = preferredUnit === desiredUnit
            ? value
            : converter.convert(value, fromUnit, desiredUnit)
        console.log(`Converting ${category}.${key}: ${value} from ${fromUnit} to ${desiredUnit} -> ${result}`)
        return result
    }
}
