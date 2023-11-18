//
// Created by miku on 11/17/2023.
//

#include "MJunctionItem.hpp"
#include "..\editor\MSinkDialog.hpp"

#include <QGraphicsSceneMouseEvent>

#include "..\editor\MJunctionDialog.hpp"

MJunctionItem::MJunctionItem(QGraphicsPixmapItem* parent)
    : MAbstractItem(Junction, "Junction", ":/resources/image/junction.png", parent),
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

bool MJunctionItem::canConnectWith(const MAbstractItem& other, const ConnectionKind kind) const {
    Q_UNUSED(other)
    Q_UNUSED(kind)

    // 😎
    return true;
}
