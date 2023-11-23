//
// Created by miku on 11/17/2023.
//

#include "MWellItem.hpp"
#include "service/EntityService.hpp"

#include <logging/logging.hpp>
#include <FluentUIExt/src/FluApp.h>

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
    // Open the QML window, and the widget-based window.
    const auto* qmlWindow = openEditorDialog(_qmlRoute);
    _wellDisplayWindow->show();
    _wellDisplayWindow->resize(300, 600);

    const auto clip = [this, qmlWindow] {
        if (!_wellDisplayWindow || !_wellDisplayWindow->isVisible()) {
            return;
        }
        // Clip _wellDisplayWindow to the left of the main window
        _wellDisplayWindow->move(
            qmlWindow->x() - _wellDisplayWindow->width(),
            qmlWindow->y()
        );
    };
    QObject::connect(qmlWindow, &QQuickWindow::xChanged, clip);
    QObject::connect(qmlWindow, &QQuickWindow::yChanged, clip);
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
