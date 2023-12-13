//
// Created by miku on 11/17/2023.
//

#include "MWellItem.hpp"
#include "service/EntityService.hpp"
#include "service/FluidDataService.hpp"
#include "widget/MainWindow.hpp"

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
    ) {
}

void MWellItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {
    auto* context = gpQmlApplicationEngine->rootContext();
    context->setContextProperty("fluidIv", FluidDataService::getInstance()->iv());

    // 帅到掀桌
    // ～(▼-▼)っ┻━┻☆.*･｡ﾟ
    if (!_bridge->isConnected(QMetaMethod::fromSignal(&MSignalBridge::onOpenBlackOilManager))) {
        QObject::connect(
            _bridge, &MSignalBridge::onOpenBlackOilManager,
            gpWindowMain, &MainWindow::openBlackOilManager);
    }

    // Open the QML window, and the widget-based window.
    const auto* qmlWindow = openEditorDialog(_qmlRoute);

    // _wellDisplayWindow = new MWellDisplayWindow{_entity, _independentVariables, nullptr};
    // _wellDisplayWindow->showAndClipTo(qmlWindow);
}

void MWellItem::onUserDataSaved() const {
    // TODO: 如存
    // _wellDisplayWindow->notifyDataChanged();
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
