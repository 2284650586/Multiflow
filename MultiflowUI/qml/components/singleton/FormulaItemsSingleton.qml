pragma Singleton

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Multiflow.UI
import FluentUI

FluObject {
    property var navigationView
    property var paneItemMenu
    property var formulae

    id: itemGroup

    function rename(item, newName) {
        if (newName && newName.trim().length > 0) {
            item.title = newName;
        }
    }

    function render() {
        itemGroup.children = []
        var component = Qt.createComponent("../widget/FormulaPaneItem.qml")
        for (var i = 0; i < formulae.length; i++) {
            var formula = formulae[i]
            if (component.status === Component.Ready) {
                var item = component.createObject(itemGroup, {
                    formula: formula,
                    navigationView: navigationView,
                })
                itemGroup.children.push(item)
            }
        }
    }

    function getRecentlyAddedData() {
        var arr = []
        for (var i = 0; i < children.length; i++) {
            var item = children[i]
            if (item instanceof FluPaneItem && item.recentlyAdded) {
                arr.push(item)
            }
            if (item instanceof FluPaneItemExpander) {
                for (var j = 0; j < item.children.length; j++) {
                    var itemChild = item.children[j]
                    if (itemChild instanceof FluPaneItem && itemChild.recentlyAdded) {
                        arr.push(itemChild)
                    }
                }
            }
        }
        arr.sort(function (o1, o2) {
            return o2.order - o1.order
        })
        return arr
    }

    function getRecentlyUpdatedData() {
        var arr = []
        var items = navigationView.getItems();
        for (var i = 0; i < items.length; i++) {
            var item = items[i]
            if (item instanceof FluPaneItem && item.recentlyUpdated) {
                arr.push(item)
            }
        }
        return arr
    }

    function getSearchData() {
        if (!navigationView) {
            return
        }
        var arr = []
        var items = navigationView.getItems();
        for (var i = 0; i < items.length; i++) {
            var item = items[i]
            if (item instanceof FluPaneItem) {
                if (item.parent instanceof FluPaneItemExpander) {
                    arr.push({title: `${item.parent.title} -> ${item.title}`, key: item.key})
                } else
                    arr.push({title: item.title, key: item.key})
            }
        }
        return arr
    }

    function startPageByItem(data) {
        navigationView.startPageByItem(data)
    }
}
