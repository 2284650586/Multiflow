//
// Created by miku on 11/17/2023.
//

#include "MWellItem.hpp"
#include "qml/main.hpp"

#include <QGraphicsSceneMouseEvent>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <logging/logging.hpp>

#include "service/EntityService.hpp"


MWellItem::MWellItem(QGraphicsPixmapItem* parent)
    : MAbstractItem(
        Well,
        "Well",
        ":/resources/image/Well.png",
        "/well-editor",
        EntityService::getInstance()->createEntity("MWell"),
        new WellCalculationUnit{},
        parent
    ) {
}

void MWellItem::onUserDataSaved() const {
    log_info("Well data saved");
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
