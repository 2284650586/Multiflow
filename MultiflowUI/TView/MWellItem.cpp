//
// Created by miku on 11/17/2023.
//

#include "MWellItem.hpp"
#include "parUI/msinkdialog.h"
#include "parUI/mwellwindow.h"

#include <QGraphicsSceneMouseEvent>

MWellItem::MWellItem(QGraphicsPixmapItem* parent)
    : MAbstractItem(Well, "Well", ":/resources/image/Well.png", parent),
      _well(new MWell{}) {
}

void MWellItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {
    event->accept();
    if (event->button() != Qt::LeftButton) {
        return;
    }

    auto* window = new MWellWindow(_well, _itemName, nullptr);
    QObject::connect(window, &MWellWindow::itemNameChange, [this](const QString& name) {
        setItemName(name);
        update();
    });
    window->show();
}

bool MWellItem::canConnectWith(const MAbstractItem& other, const ConnectionKind kind) const {
    switch (kind) {
        case START_TO_END:
            return countStartArrows() == 0
                   && other.itemKind() != Well
                   && other.itemKind() != Source;

        case END_TO_START:
            return countEndArrows() == 0
                   && other.itemKind() != Source;

        default:
            return false;
    }
}
