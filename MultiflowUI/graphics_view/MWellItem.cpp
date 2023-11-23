//
// Created by miku on 11/17/2023.
//

#include "MWellItem.hpp"
#include "service/EntityService.hpp"

#include <logging/logging.hpp>
#include <FluentUI/src/FluApp.h>

#include <QQmlApplicationEngine>
#include <QTimer>


MWellItem::MWellItem(QGraphicsPixmapItem* parent)
    : MAbstractItem(
        Well,
        "Well",
        ":/resources/image/Well.png",
        "/well-editor",
        EntityService::getInstance()->createEntity("MWell"),
        new WellCalculationUnit{},
        parent
    ), _wellDisplayWindow(new MWellDisplayWindow{_entity}) {
}

void MWellItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {
    // Call the base class implementation for QML window
    MAbstractItem::mouseDoubleClickEvent(event);
    QTimer::singleShot(5000, [this] () {
        const auto* window = gpQmlApplicationEngine->rootObjects()
            .first()->findChild<QQuickWindow*>("WellEditorWindow");

        _wellDisplayWindow->show();
        _wellDisplayWindow->resize(300, 600);

        // Clip _wellDisplayWindow to the left of the main window
        _wellDisplayWindow->move(
            window->x() - _wellDisplayWindow->width(),
            window->y()
        );
    });
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
