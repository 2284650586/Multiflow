//
// Created by miku on 11/17/2023.
//

#include "MJunctionItem.hpp"
#include "editor/MSinkDialog.hpp"
#include "editor/MJunctionDialog.hpp"

#include <QGraphicsSceneMouseEvent>

MJunctionItem::MJunctionItem(QGraphicsPixmapItem* parent)
    : MAbstractItem(Junction, "Junction", ":/resources/image/junction.png", "", nullptr, nullptr, parent),
      _junction(new MJunction{}) {
}

void MJunctionItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {
    event->accept();
    if (event->button() != Qt::LeftButton) {
        return;
    }

    auto* dialog = new MJunctionDialog(_junction, _itemName, nullptr);
    dialog->exec();
    update();
}

void MJunctionItem::onUserDataSaved() const {
}

bool MJunctionItem::canConnectWith(const MAbstractItem& other, const ConnectionKind kind) const {
    Q_UNUSED(other)
    Q_UNUSED(kind)

    // 😎
    return true;
}
