//
// Created by miku on 11/17/2023.
//

#include "MSinkItem.hpp"
#include "editor/MSinkDialog.hpp"

#include <QGraphicsSceneMouseEvent>

MSinkItem::MSinkItem(QGraphicsPixmapItem* parent)
    : MAbstractItem(Sink, "Sink", ":/resources/image/sink.png", parent),
      _sink(new MSink{}) {
}

void MSinkItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {
    event->accept();
    if (event->button() != Qt::LeftButton) {
        return;
    }

    auto* dialog = new MSinkDialog(_sink, _itemName, nullptr);
    dialog->exec();
    update();
}

bool MSinkItem::canConnectWith(const MAbstractItem& other, const ConnectionKind kind) const {
    switch (kind) {
        case START_TO_END:
            return countStartArrows() == 0 && other.itemKind() != Sink;

        case END_TO_START:
            return countEndArrows() == 0;

        default:
            return false;
    }
}
