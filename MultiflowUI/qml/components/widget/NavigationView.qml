import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Controls.Basic
import QtQuick.Layouts
import FluentUI

Item {
    id: control
    property url logo
    property string title: ""
    property var model
    property var itemDelegate
    property int displayMode: FluNavigationViewType.Auto
    property Component autoSuggestBox
    property Component actionItem
    property int topPadding: 0
    property int cellHeight: 38
    property int cellWidth: 300
        signal
    logoClicked

    Item {
        id: d
        property bool animDisabled: false
        property var stackItems: []
        property int displayMode: control.displayMode
        property bool enableNavigationPanel: false
        property bool isCompact: d.displayMode === FluNavigationViewType.Compact
        property bool isMinimal: d.displayMode === FluNavigationViewType.Minimal
        property bool isCompactAndPanel: d.displayMode === FluNavigationViewType.Compact && d.enableNavigationPanel
        property bool isCompactAndNotPanel: d.displayMode === FluNavigationViewType.Compact && !d.enableNavigationPanel
        property bool isMinimalAndPanel: d.displayMode === FluNavigationViewType.Minimal && d.enableNavigationPanel
        property color itemDisableColor: FluTheme.dark ? Qt.rgba(131 / 255, 131 / 255, 131 / 255, 1) : Qt.rgba(160 / 255, 160 / 255, 160 / 255, 1)
        onIsCompactAndNotPanelChanged: {
            collapseAll()
        }
    }

    Timer {
        id: timerAnimDelay
        interval: 200
        onTriggered: {
            d.animDisabled = true
        }
    }

    Component.onCompleted: {
        d.displayMode = Qt.binding(() => {
            if (control.displayMode !== FluNavigationViewType.Auto) {
                return control.displayMode
            }
            if (control.width <= 700) {
                return FluNavigationViewType.Minimal
            }
            if (control.width <= 900) {
                return FluNavigationViewType.Compact
            }
            return FluNavigationViewType.Open
        })
        timerAnimDelay.restart()
    }

    Connections {
        target: d

        function onDisplayModeChanged() {
            if (d.displayMode === FluNavigationViewType.Compact) {
                collapseAll()
            }
            d.enableNavigationPanel = false
            if (loader_auto_suggest_box.item) {
                loader_auto_suggest_box.item.focus = false
            }
        }
    }

    Component {
        id: com_panel_item
        Item {
            Behavior on height {
                enabled: FluTheme.enableAnimation && d.animDisabled
                NumberAnimation {
                    duration: 167
                    easing.type: Easing.OutCubic
                }
            }
            height: {
                if (paneItem && paneItem._parent) {
                    return paneItem._parent.isExpand ? control.cellHeight : 0
                }
                return control.cellHeight
            }
            visible: control.cellHeight === Number(height)
            opacity: visible
            Behavior on opacity {
                NumberAnimation {
                    duration: 83
                }
            }
            width: layout_list.width

            FluControl {
                property var modelData: paneItem
                id: item_control
                enabled: !paneItem.disabled
                anchors {
                    top: parent.top
                    bottom: parent.bottom
                    left: parent.left
                    right: parent.right
                    topMargin: 2
                    bottomMargin: 2
                    leftMargin: 6
                    rightMargin: 6
                }
                FluTooltip {
                    text: paneItem.title
                    visible: item_control.hovered && paneItem.title && d.isCompact
                    delay: 400
                }
                onClicked: {
                    if (paneItem.onTapListener) {
                        paneItem.onTapListener()
                    } else {
                        nav_list.currentIndex = idx
                        paneItem.tap()
                        if (d.isMinimal || d.isCompact) {
                            d.enableNavigationPanel = false
                        }
                    }
                }
                MouseArea {
                    id: item_mouse
                    anchors.fill: parent
                    acceptedButtons: Qt.RightButton | Qt.LeftButton
                    onClicked:
                            (mouse) => {
                        if (mouse.button === Qt.RightButton) {
                            if (paneItem.menuDelegate) {
                                loader_item_menu.sourceComponent = paneItem.menuDelegate
                                connection_item_menu.target = loader_item_menu.item
                                loader_item_menu.modelData = paneItem
                                loader_item_menu.item.popup();
                            }
                        } else {
                            item_control.clicked()
                        }
                    }
                }
                Rectangle {
                    radius: 4
                    anchors.fill: parent
                    color: {
                        if (!item_control.enabled) {
                            return FluTheme.itemNormalColor
                        }
                        if (nav_list.currentIndex === idx) {
                            return FluTheme.itemCheckColor
                        }
                        if (item_control.hovered) {
                            return FluTheme.itemHoverColor
                        }
                        return FluTheme.itemNormalColor
                    }
                    Component {
                        id: com_icon
                        FluIcon {
                            iconSource: {
                                if (paneItem && paneItem.icon) {
                                    return paneItem.icon
                                }
                                return 0
                            }
                            color: {
                                if (!item_control.enabled) {
                                    return d.itemDisableColor
                                }
                                return FluTheme.dark ? "#FFFFFF" : "#000000"
                            }
                            iconSize: 15
                        }
                    }
                    Item {
                        id: item_icon
                        height: 30
                        width: com_panel_item.visible ? 30 : 8
                        visible: {
                            if (item_control.paneItem) {
                                return item_control.paneItem.iconVisible
                            }
                            return true
                        }
                        anchors {
                            verticalCenter: parent.verticalCenter
                            left: parent.left
                            leftMargin: 3
                        }
                        FluLoader {
                            anchors.centerIn: parent
                            Component.onDestruction: sourceComponent = undefined
                            sourceComponent: {
                                if (item_control.paneItem && item_control.paneItem.iconDelegate) {
                                    return item_control.paneItem.iconDelegate
                                }
                                return com_icon
                            }
                        }
                    }
                    FluText {
                        id: item_title
                        text: {
                            if (paneItem) {
                                if (!item_icon.visible && d.isCompactAndNotPanel) {
                                    return paneItem.title[0]
                                }
                                return paneItem.title
                            }
                            return ""
                        }
                        visible: {
                            if (d.isCompactAndNotPanel) {
                                if (item_icon.visible) {
                                    return false
                                }
                                return true
                            }
                            return true
                        }
                        elide: Text.ElideRight
                        color: {
                            if (!item_control.enabled) {
                                return d.itemDisableColor
                            }
                            if (item_mouse.pressed) {
                                return FluTheme.dark ? FluColors.Grey80 : FluColors.Grey120
                            }
                            return FluTheme.dark ? FluColors.White : FluColors.Grey220
                        }
                        anchors {
                            verticalCenter: parent.verticalCenter
                            left: item_icon.right
                            right: item_dot_loader.left
                        }
                    }
                    FluLoader {
                        id: item_edit_loader
                        anchors {
                            top: parent.top
                            bottom: parent.bottom
                            left: item_title.left
                            right: item_title.right
                            rightMargin: 8
                        }
                        sourceComponent: {
                            if (d.isCompact) {
                                return undefined
                            }
                            if (!paneItem) {
                                return undefined
                            }
                            return paneItem.showEdit ? paneItem.editDelegate : undefined
                        }
                        Component.onDestruction: sourceComponent = undefined
                        onStatusChanged: {
                            if (status === FluLoader.Ready) {
                                item.forceActiveFocus()
                                item_connection_edit_focus.target = item
                            }
                        }
                        Connections {
                            id: item_connection_edit_focus
                            ignoreUnknownSignals: true

                            function onActiveFocusChanged(focus) {
                                if (focus === false) {
                                    paneItem.showEdit = false
                                }
                            }

                            function onCommit(text) {
                                paneItem.title = text
                                paneItem.showEdit = false
                            }
                        }
                    }
                    FluLoader {
                        id: item_dot_loader
                        property bool isDot: (item_dot_loader.item && item_dot_loader.item.isDot)
                        anchors {
                            right: parent.right
                            verticalCenter: parent.verticalCenter
                            rightMargin: isDot ? 3 : 10
                            verticalCenterOffset: isDot ? -8 : 0
                        }
                        sourceComponent: {
                            if (paneItem && paneItem.infoBadge) {
                                return paneItem.infoBadge
                            }
                            return undefined
                        }
                        Component.onDestruction: sourceComponent = undefined
                        Connections {
                            target: d

                            function onIsCompactAndNotPanelChanged() {
                                if (item_dot_loader.item) {
                                    item_dot_loader.item.isDot = d.isCompactAndNotPanel
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Item {
        id: nav_app_bar
        width: parent.width
        height: 40
        anchors {
            top: parent.top
            topMargin: control.topPadding
        }
        z: 999
        RowLayout {
            height: parent.height
            spacing: 0
            FluIconButton {
                id: btn_back
                iconSource: FluentIcons.ChromeBack
                Layout.leftMargin: 5
                Layout.alignment: Qt.AlignVCenter
                disabled: {
                    return d.stackItems.length <= 1
                }
                iconSize: 13
                onClicked: {
                    d.stackItems = d.stackItems.slice(0, -1)
                    var item = d.stackItems[d.stackItems.length - 1]
                    nav_list.currentIndex = item.index
                    loader_content.setSource(item._ext.url, item._ext.argument)
                }
            }
            FluIconButton {
                id: btn_nav
                iconSource: FluentIcons.GlobalNavButton
                iconSize: 15
                Layout.preferredWidth: d.isMinimal ? 30 : 0
                Layout.preferredHeight: 30
                Layout.alignment: Qt.AlignVCenter
                clip: true
                onClicked: {
                    d.enableNavigationPanel = !d.enableNavigationPanel
                }
                visible: opacity
                opacity: d.isMinimal
                Behavior on opacity {
                    enabled: FluTheme.enableAnimation && d.animDisabled
                    NumberAnimation {
                        duration: 83
                    }
                }
                Behavior on Layout
                .
                preferredWidth {
                    enabled: FluTheme.enableAnimation && d.animDisabled
                    NumberAnimation {
                        duration: 167
                        easing.type: Easing.OutCubic
                    }
                }
            }
            Image {
                id: image_logo
                Layout.preferredHeight: 20
                Layout.preferredWidth: 20
                source: control.logo
                Layout.leftMargin: {
                    if (btn_nav.visible) {
                        return 12
                    }
                    return 5
                }
                sourceSize: Qt.size(40, 40)
                Layout.alignment: Qt.AlignVCenter
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        logoClicked()
                    }
                }
            }
            FluText {
                Layout.alignment: Qt.AlignVCenter
                text: control.title
                Layout.leftMargin: 12
                font: FluTextStyle.Body
            }
        }
        Item {
            anchors.right: parent.right
            height: parent.height
            width: {
                if (loader_action.item) {
                    return loader_action.item.width
                }
                return 0
            }
            FluLoader {
                id: loader_action
                anchors.centerIn: parent
                sourceComponent: actionItem
                Component.onDestruction: sourceComponent = undefined
            }
        }
    }

    Component {
        id: com_stack_content
        Item {
            StackView {
                id: nav_stack
                anchors.fill: parent
                clip: true
                visible: !nav_stack2.visible
                popEnter: Transition {
                }
                popExit: Transition {
                }
                pushEnter: Transition {
                }
                pushExit: Transition {
                }
                replaceEnter: Transition {
                }
                replaceExit: Transition {
                }
            }
            StackLayout {
                id: nav_stack2
                anchors.fill: nav_stack
                clip: true
                visible: {
                    if (!nav_stack.currentItem) {
                        return false
                    }
                    return FluPageType.SingleInstance === nav_stack.currentItem.launchMode
                }
            }

            function navStack() {
                return nav_stack
            }

            function navStack2() {
                return nav_stack2
            }
        }
    }
    FluLoader {
        id: loader_content
        anchors {
            left: parent.left
            top: nav_app_bar.bottom
            right: parent.right
            bottom: parent.bottom
            leftMargin: {
                if (d.isMinimal) {
                    return 0
                }
                if (d.isCompact) {
                    return 50
                }
                return control.cellWidth
            }
        }
        Component.onDestruction: sourceComponent = undefined
        Behavior on anchors.leftMargin {
            enabled: FluTheme.enableAnimation && d.animDisabled
            NumberAnimation {
                duration: 167
                easing.type: Easing.OutCubic
            }
        }
        sourceComponent: com_stack_content
    }
    MouseArea {
        anchors.fill: parent
        visible: d.isMinimalAndPanel || d.isCompactAndPanel
        hoverEnabled: true
        onWheel: {
        }
        onClicked: {
            d.enableNavigationPanel = false
        }
    }
    Rectangle {
        id: layout_list
        width: {
            if (d.isCompactAndNotPanel) {
                return 50
            }
            return control.cellWidth
        }
        anchors {
            top: parent.top
            bottom: parent.bottom
        }
        border.color: FluTheme.dark ? Qt.rgba(45 / 255, 45 / 255, 45 / 255, 1) : Qt.rgba(226 / 255, 230 / 255, 234 / 255, 1)
        border.width: d.isMinimal || d.isCompactAndPanel ? 1 : 0
        color: {
            if (d.isMinimal || d.enableNavigationPanel) {
                return FluTheme.dark ? Qt.rgba(61 / 255, 61 / 255, 61 / 255, 1) : Qt.rgba(243 / 255, 243 / 255, 243 / 255, 1)
            }
            return "transparent"
        }
        FluShadow {
            visible: d.isMinimal || d.isCompactAndPanel
            radius: 0
        }
        x: visible ? 0 : -width
        Behavior on width {
            enabled: FluTheme.enableAnimation && d.animDisabled
            NumberAnimation {
                duration: 167
                easing.type: Easing.OutCubic
            }
        }
        Behavior on x {
            enabled: FluTheme.enableAnimation && d.animDisabled
            NumberAnimation {
                duration: 167
                easing.type: Easing.OutCubic
            }
        }
        visible: {
            if (d.displayMode !== FluNavigationViewType.Minimal)
                return true
            return d.isMinimalAndPanel ? true : false
        }
        Item {
            id: layout_header
            width: layout_list.width
            clip: true
            y: nav_app_bar.height + control.topPadding
            height: autoSuggestBox ? 38 : 0
            FluLoader {
                id: loader_auto_suggest_box
                sourceComponent: autoSuggestBox
                anchors {
                    left: parent.left
                    right: parent.right
                    leftMargin: 6
                    rightMargin: 6
                    verticalCenter: parent.verticalCenter
                }
                Component.onDestruction: sourceComponent = undefined
                visible: {
                    if (d.isCompactAndNotPanel) {
                        return false
                    }
                    return true
                }
            }
            FluIconButton {
                visible: d.isCompactAndNotPanel
                width: 38
                height: 34
                x: 6
                y: 2
                iconSize: 15
                iconSource: {
                    if (loader_auto_suggest_box.item) {
                        return loader_auto_suggest_box.item.autoSuggestBoxReplacement
                    }
                    return 0
                }
                onClicked: {
                    d.enableNavigationPanel = !d.enableNavigationPanel
                }
            }
        }
        Flickable {
            id: layout_flickable
            anchors {
                top: layout_header.bottom
                topMargin: 6
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }
            boundsBehavior: ListView.StopAtBounds
            clip: true
            contentHeight: nav_list.contentHeight
            ScrollBar.vertical: FluScrollBar {
            }
            ListView {
                id: nav_list
                clip: true
                displaced: Transition {
                    NumberAnimation {
                        properties: "x,y"
                        easing.type: Easing.OutQuad
                    }
                }
                anchors.fill: parent
                interactive: false
                model: control.model
                boundsBehavior: ListView.StopAtBounds
                highlightMoveDuration: FluTheme.enableAnimation && d.animDisabled ? 167 : 0
                highlight: Item {
                    clip: true
                    Rectangle {
                        height: 18
                        radius: 1.5
                        color: FluTheme.primaryColor
                        width: 3
                        anchors {
                            verticalCenter: parent.verticalCenter
                            left: parent.left
                            leftMargin: 6
                        }
                    }
                }
                currentIndex: -1
                delegate: FluLoader {
                    property var paneItem: itemDelegate(modelData, index)
                    property var idx: index
                    property int type: 0
                    Component.onDestruction: sourceComponent = undefined
                    sourceComponent: {
                        if (modelData === null || !modelData) {
                            console.log("modelData is null")
                            return undefined
                        }
                        return com_panel_item
                    }
                }
            }
        }
    }
    Popup {
        property var childModel
        id: control_popup
        enter: Transition {
            NumberAnimation {
                property: "opacity"
                from:0
                to: 1
                duration: 83
            }
        }
        Connections {
            target: d

            function onIsCompactChanged() {
                if (!d.isCompact) {
                    control_popup.close()
                }
            }
        }
        padding: 0
        focus: true
        contentItem: Item {
            ListView {
                id: list_view
                anchors.fill: parent
                clip: true
                currentIndex: -1
                model: control_popup.childModel
                boundsBehavior: ListView.StopAtBounds
                ScrollBar.vertical: FluScrollBar {
                }
                delegate: Button {
                    id: item_button
                    width: 180
                    height: 38
                    focusPolicy: Qt.TabFocus
                    background: Rectangle {
                        color: {
                            if (item_button.hovered) {
                                return FluTheme.itemHoverColor
                            }
                            return FluTheme.itemNormalColor
                        }
                        FluFocusRectangle {
                            visible: item_button.activeFocus
                            radius: 4
                        }

                        FluLoader {
                            id: item_dot_loader
                            anchors {
                                right: parent.right
                                verticalCenter: parent.verticalCenter
                                rightMargin: 10
                            }
                            Component.onDestruction: sourceComponent = undefined
                            sourceComponent: {
                                if (model.infoBadge) {
                                    return model.infoBadge
                                }
                                return undefined
                            }
                        }

                    }
                    contentItem: FluText {
                        text: modelData.title
                        elide: Text.ElideRight
                        rightPadding: item_dot_loader.width
                        verticalAlignment: Qt.AlignVCenter
                        anchors {
                            verticalCenter: parent.verticalCenter
                        }
                    }
                    onClicked: {
                        if (modelData.onTapListener) {
                            modelData.onTapListener()
                        } else {
                            modelData.tap()
                            nav_list.currentIndex = index
                            if (d.isMinimal || d.isCompact) {
                                d.enableNavigationPanel = false
                            }
                        }
                        control_popup.close()
                    }
                }
            }
        }
        background: FluRectangle {
            implicitWidth: 180
            radius: [4, 4, 4, 4]
            FluShadow {
                radius: 4
            }
            color: FluTheme.dark ? Qt.rgba(51 / 255, 48 / 255, 48 / 255, 1) : Qt.rgba(248 / 255, 250 / 255, 253 / 255, 1)
        }

        function showPopup(pos, height, model) {
            background.implicitHeight = height
            control_popup.x = pos.x
            control_popup.y = pos.y
            control_popup.childModel = model
            control_popup.open()
        }
    }
    FluLoader {
        property var modelData
        Component.onDestruction: sourceComponent = undefined
        id: loader_item_menu
    }
    Connections {
        id: connection_item_menu

        function onVisibleChanged(visible) {
            if (target.visible === false) {
                loader_item_menu.sourceComponent = undefined
            }
        }
    }
    Component {
        id: com_placeholder
        Item {
            property int launchMode: FluPageType.SingleInstance
            property string url
        }
    }

    function collapseAll() {
        for (var i = 0; i < nav_list.model.length; i++) {
            var item = nav_list.model[i]
            if (item instanceof FluPaneItemExpander) {
                item.isExpand = false
            }
        }
    }

    function setCurrentIndex(index) {
        nav_list.currentIndex = index
        var item = nav_list.model[index]
        if (item instanceof FluPaneItem) {
            item.tap()
        }
    }

    function getItems() {
        return nav_list.model
    }

    function getCurrentIndex() {
        return nav_list.currentIndex
    }

    function getCurrentUrl() {
        return loader_content.source.toString()
    }

    function push(url, argument = {}) {
        if (loader_content.source.toString() === url) {
            return
        }
        loader_content.setSource(url, argument)
        var obj = nav_list.model[nav_list.currentIndex]
        obj._ext = {url: url, argument: argument}
        d.stackItems = d.stackItems.concat(obj)
    }

    function startPageByItem(data) {
        var items = getItems()
        for (var i = 0; i < items.length; i++) {
            var item = items[i]
            if (item.key === data.key) {
                if (getCurrentIndex() === i) {
                    return
                }
                setCurrentIndex(i)
                if (item._parent && !d.isCompactAndNotPanel) {
                    item._parent.isExpand = true
                }
                return
            }
        }
    }

    function backButton() {
        return btn_back
    }

    function navButton() {
        return btn_nav
    }

    function logoButton() {
        return image_logo
    }
}
