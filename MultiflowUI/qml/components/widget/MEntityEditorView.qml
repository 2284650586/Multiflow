import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Multiflow.UI
import FluentUI
import Qt.labs.qmlmodels
import "qrc:/qml/components/widget/"
import "qrc:/qml/components/singleton/"

Item {
    required property var entity            /* QVariant(MEntity*) */
    required property var iv                /* QVariant(MIndependentVariables*) */
    required property var calculationUnit   /* QVariant(MAbstractCalculationUnit*) */
    required property string category

    property bool hideDefaultCalculateButton: false

    /**
     * {
     *     text: string,
     *     onClicked: function({
     *       category,
     *       row,
     *       iv,
     *       tableView,
     *       entity,
     *       notifyPartialDataChange,
     *     })
     * }
     */
    property var extraRowActions: []

    signal onDataPartiallyChanged(var entity)

    signal onReloadTableDataSource()

    signal onDataEvaluated(var results)

    id: control

    QtObject {
        property var keys: []
        property var hfKeys: []
        property int maxTextFieldWidth: 0

        id: g
        Component.onCompleted: {
            reloadKeys()
        }
    }

    ColumnLayout {
        id: layoutContext
        anchors.fill: parent
        Component.onCompleted: {
            onReloadTableDataSource.connect(tryReloadTableDataSource)
        }

        Repeater {
            id: repeater
            model: g.keys
            Layout.fillWidth: true
            Layout.fillHeight: true
            onCountChanged: {
                if (count === g.keys.length) {
                    rearrange()
                }
            }

            RowLayout {
                property var key: modelData
                property var currentEntity: entity[key]
                property FluText label: label

                spacing: 8
                Layout.fillWidth: true

                FluText {
                    id: label
                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                    font.pointSize: 11
                    font.weight: Font.DemiBold

                    Component.onCompleted: {
                        label.text = `${currentEntity.name}: `
                    }
                }

                Loader {
                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                    Layout.preferredWidth: 200
                    sourceComponent: getComponentId(currentEntity)

                    Component {
                        id: componentTextField

                        FluTextBox {
                            id: textBoxString
                            Layout.preferredHeight: 26
                            onTextChanged: {
                                currentEntity.value = text
                            }

                            Component.onCompleted: {
                                textBoxString.text = currentEntity.value
                            }
                        }
                    }

                    Component {
                        id: componentEnum

                        RowLayout {
                            spacing: 0
                            FluComboBox {
                                property var items: currentEntity.extra.split(", ")

                                id: comboBoxEnum
                                model: items
                                currentIndex: -1
                                Layout.preferredWidth: 200
                                Layout.preferredHeight: 26
                                Layout.fillHeight: true
                                Component.onCompleted: {
                                    comboBoxEnum.currentIndex = currentEntity.value ? items.indexOf(currentEntity.value) : 0
                                    comboBoxEnum.onCurrentTextChanged.connect(onSelected)
                                }

                                function onSelected() {
                                    currentEntity.value = currentText
                                    reloadKeys()

                                    // I don't know how `onReloadTableDataSource` can be undefined,
                                    // it is a static signal. But QML reports the error from time to time.
                                    try {
                                        onReloadTableDataSource()
                                        notifyPartialDataChange()
                                    } catch (_) {
                                    }
                                }
                            }
                        }

                    }

                    Component {
                        id: componentConverter

                        RowLayout {
                            property var units: currentEntity.extra.units()
                            spacing: 4

                            FluTextBox {
                                id: textBox
                                Layout.preferredWidth: 121
                                Layout.preferredHeight: 26
                                Layout.fillHeight: true
                                onTextChanged: {
                                    currentEntity.value = text
                                }
                                Component.onCompleted: {
                                    textBox.text = currentEntity.value
                                }
                            }

                            FluComboBox {
                                property var lastUnit: currentEntity.associateValue
                                    ? units[currentEntity.associateValue]
                                    : (currentEntity.preferredUnit || units[0])

                                id: comboBox
                                model: units
                                Layout.preferredWidth: 75
                                Layout.preferredHeight: 26
                                Layout.fillHeight: true
                                Component.onCompleted: {
                                    comboBox.currentIndex = currentEntity.associateValue ? currentEntity.associateValue : 0
                                }
                                onCurrentTextChanged: {
                                    if (!MUtils.isNumeric(textBox.text)) {
                                        return
                                    }
                                    let oldValue = parseFloat(textBox.text)
                                    let newUnit = currentText
                                    let newValue = currentEntity.extra.convert(oldValue, lastUnit, newUnit)
                                    newValue = Number(newValue.toFixed(4))
                                    textBox.text = `${newValue}`
                                    currentEntity.associateValue = currentIndex
                                    lastUnit = currentText
                                }
                            }
                        }
                    }

                    function getComponentId(entity) {
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

            function rearrange() {
                updateMaxWidth(repeater, repeater.model.length, 'label')
            }
        } // Repeater

        Item {
            Layout.preferredHeight: 8
        }

        // 好！表格区域！
        Component {
            id: componentTableArea

            FluArea {
                property var hidHfKeys: getHidHfKeys()
                //! property var dataSource: []

                id: hfArea
                visible: g.hfKeys.length > 0 && hidHfKeys.length !== g.hfKeys.length
                radius: 8
                clip: true
                Component.onCompleted: {
                    tableView.cellUpdated.connect(onTableViewCellUpdated)
                    tableView.associateValueUpdated.connect(onAssociateValueUpdated)
                    iv.sizeChanged.connect(onIndependentVariablesSizeChanged)
                }

                FluentExtTableView {
                    id: tableView
                    radius: 8
                    color: "transparent"
                    anchors.fill: parent

                    // FluTableView左边有一个迷之1像素的空白
                    // 通过设置leftMargin为-1来抵消
                    anchors.leftMargin: -1

                    // Must bind directly, and immediately
                    // or the table will never be shown
                    columnSource: getColumnSource()
                    ivRef: iv
                    categoryRef: category
                    Component.onCompleted: {
                        reloadDataSource()
                    }
                    Component {
                        id: componentActionArea
                        RowLayout {
                            anchors.fill: parent

                            FluButton {
                                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                                text: "删除"
                                Layout.preferredHeight: 26
                                onClicked: handleDeleteSingleRow()
                            }

                            Repeater {
                                model: extraRowActions
                                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                                delegate: FluFilledButton {
                                    text: modelData.text
                                    Layout.preferredHeight: 26
                                    onClicked: modelData.onClicked({
                                        category: category,
                                        row: row,
                                        iv: iv,
                                        tableView: tableView,
                                        entity: entity,
                                        notifyPartialDataChange: notifyPartialDataChange,
                                    })
                                }
                            }

                            function handleDeleteSingleRow() {
                                notifyPartialDataChange()
                                tableView.closeEditor()
                                iv.remove(category, row)
                                tableView.reloadDataSource && tableView.reloadDataSource()
                            }
                        }
                    }

                    function getColumnSource() {
                        const columns = []
                        for (const key of g.hfKeys) {
                            const property = entity[key]

                            // It's not possible to dynamically change the columns
                            // because they are final in the TableModel. 难过
                            // However, we could just hide it with a 1px width
                            const shouldHide = hidHfKeys.includes(key)

                            columns.push({
                                title: shouldHide ? '' : property.name,
                                type: shouldHide ? 'string' : property.type,
                                extra: property.extra,
                                dataIndex: key,
                                example: property.example,
                                initialValue: property.value,
                                associateValue: property.associateValue,
                                preferredUnit: property.preferredUnit,
                                shouldDisable: property.shouldDisable,
                                minimumWidth: shouldHide ? 1 : 40,
                                maximumWidth: shouldHide ? 1 : 300,
                                width: shouldHide ? 1 : 80,
                            })
                        }
                        // Reserve a column for actions
                        columns.push({title: "操作", dataIndex: "action"})
                        return columns
                    }

                    function getDataSource() {
                        const rows = []
                        const size = iv.size(category)
                        const hfKeys = getHfKeys()

                        // Fill in row data
                        for (let i = 0; i < size; ++i) {
                            const row = {}
                            for (const key of hfKeys) {
                                const shouldHide = hidHfKeys.includes(key)
                                if (shouldHide) {
                                    row[key] = ""
                                    continue
                                }

                                const actual = iv.get(category, i, key)
                                if (actual) {
                                    row[key] = actual
                                    continue
                                }

                                const example = entity[key].example
                                if (example) {
                                    iv.set(category, i, key, example)
                                    row[key] = example
                                    continue
                                }
                                row[key] = ""
                            }
                            row['action'] = tableView.customItem(componentActionArea)
                            row['height'] = 30
                            rows.push(row)
                        }
                        return rows
                    }

                    function reloadDataSource() {
                        tableView.dataSource = getDataSource()
                    }

                    function reloadColumnSource() {
                        tableView.columnSource = getColumnSource()
                    }
                }

                function onAssociateValueUpdated(property, value) {
                    entity[property.dataIndex].associateValue = value
                    notifyPartialDataChange()
                }

                function onTableViewCellUpdated(row, column, value) {
                    const key = g.hfKeys[column]
                    iv.set(category, row, key, value)
                    notifyPartialDataChange()
                }

                function onIndependentVariablesSizeChanged(associatedCategory) {
                    if (associatedCategory !== category) {
                        return
                    }
                    tableView.reloadDataSource()
                }

                function getTableView() {
                    return tableView
                }
            } // FluArea
        }
        Loader {
            id: tableLoader
            Layout.fillWidth: true
            Layout.fillHeight: true
            sourceComponent: g.hfKeys.length > 0 ? componentTableArea : null
        }

        RowLayout {
            Layout.fillWidth: true

            FluButton {
                visible: g.hfKeys.length > 0
                text: "添加一组数据"
                Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
                onClicked: handleCreateNewRow()

                function handleCreateNewRow() {
                    iv.createEmpty(category)
                    const lastIndex = iv.size(category) - 1

                    // Initialize iv
                    const keys = getHfKeys()
                    for (const key of keys) {
                        const initialValue = entity[key].value
                        if (initialValue) {
                            iv.set(category, lastIndex, key, initialValue)
                        }
                    }

                    // Reload table data source
                    const hfArea = tableLoader.item
                    if (hfArea) {
                        hfArea.getTableView().reloadDataSource()
                    }
                    notifyPartialDataChange()
                }
            }

            HSpacer {
            }

            FluFilledButton {
                visible: calculationUnit && !hideDefaultCalculateButton && (g.keys.length > 0 || g.hfKeys.length > 0)
                text: "计算"
                Layout.alignment: Qt.AlignRight | Qt.AlignBottom
                onClicked: handleCalculation()
            }

            FluButton {
                text: "保存"
                Layout.alignment: Qt.AlignRight | Qt.AlignBottom
                onClicked: handleSaveExit()
            }
        }

        function tryReloadTableDataSource() {
            const hfArea = tableLoader.item
            if (hfArea) {
                const tableView = hfArea.getTableView()
                tableView.closeEditor()
                tableView.reloadDataSource()
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

    function handleSaveExit() {
        notifyPartialDataChange()
        window.close()
    }

    function handleCalculation() {
        if (!calculationUnit) {
            showAlert("无法计算", `此模型类型 ${entity.name.value} (${category}) 不具有计算功能~`)
            return
        }
        if (iv.size(category) === 0) {
            showAlert("无法计算", "请添加至少一组数据")
            return
        }
        calculationUnit.update(entity, iv)
        const results = calculationUnit.evaluate(category)
        onDataEvaluated(results)
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

    function reloadKeys() {
        g.keys = getKeys()
        g.hfKeys = getHfKeys()
    }

    function notifyPartialDataChange() {
        onDataPartiallyChanged(entity)
    }

    function getKeys() {
        return MUtils.wrapMEntityKeys(entity.keys()).filter(
                k => !entity[k].isHighFrequency
                && entity[k].shouldShow(entity)
        )
    }

    function getHfKeys() {
        return MUtils.wrapMEntityKeys(entity.keys()).filter(
                k => entity[k].isHighFrequency
        )
    }

    function getHidHfKeys() {
        return MUtils.wrapMEntityKeys(entity.keys()).filter(
                k => entity[k].isHighFrequency
                && !entity[k].shouldShow(entity)
        )
    }

    function showAlert(title, message) {
        dialog.dialogTitle = title
        dialog.dialogMessage = message
        dialog.open()
    }
}
