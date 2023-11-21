#include "MTreeWidget.hpp"

#include <QIcon>
#include <QSize>

MTreeWidget::MTreeWidget(QWidget* parent) : QTreeWidget(parent) {
    _font = headerItem()->font(0);
    _font.setPixelSize(15);

    headerItem()->setFont(0, _font);
    headerItem()->setText(0, "输入组件");
}

QTreeWidgetItem* MTreeWidget::_makeItem(const QString& name, const QString& iconPath) {
    auto item = new QTreeWidgetItem{this};
    item->setFont(0, _font);
    item->setText(0, name);
    item->setIcon(0, QIcon{iconPath});
    item->setExpanded(true);
    return item;
}

void MTreeWidget::initializeItems() {
    if (_didInitialized) {
        return;
    }
    _didInitialized = true;
    _items = QVector<QTreeWidgetItem*>{
        _makeItem("油井", ":/resources/image/Well.png"),
        _makeItem("源", ":/resources/image/source.png"),
        _makeItem("Sink", ":/resources/image/sink.png"),
        _makeItem("接合点", ":/resources/image/junction.png"),
        _makeItem("管道", ":/resources/image/flowline.png")
    };
}

void MTreeWidget::clearItems() {
    _didInitialized = false;
    clear();
}
