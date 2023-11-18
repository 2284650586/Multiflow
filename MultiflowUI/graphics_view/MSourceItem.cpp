//
// Created by miku on 11/17/2023.
//

#include "MSourceItem.hpp"
#include "..\editor\MSourceDialog.hpp"

#include <QGraphicsSceneMouseEvent>

MSourceItem::MSourceItem(QGraphicsPixmapItem* parent)
    : MAbstractItem(Source, "Source", ":/resources/image/source.png", parent),
      _source(new MSource{}) {
}

void MSourceItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {
    event->accept();
    if (event->button() != Qt::LeftButton) {
        return;
    }

    auto* dialog = new MSourceDialog(_source, _itemName, nullptr);
    dialog->exec();
    update();
}

bool MSourceItem::canConnectWith(const MAbstractItem& other, const ConnectionKind kind) const {
    switch (kind) {
        case START_TO_END:
            return countStartArrows() == 0
                   && other.itemKind() != Well
                   && other.itemKind() != Source;

        case END_TO_START:
            return countEndArrows() == 0
                   && other.itemKind() != Well;

        default:
            return false;
    }
}
