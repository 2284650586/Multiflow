//
// Created by miku on 11/17/2023.
//

#include "MWellItem.hpp"
#include "qml/main.hpp"

#include <QGraphicsSceneMouseEvent>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <logging/logging.hpp>

#include "qml/bridge/MSignalBridge.hpp"
#include "service/EntityService.hpp"


MWellItem::MWellItem(QGraphicsPixmapItem* parent)
    : MAbstractItem(Well, "Well", ":/resources/image/Well.png", parent) {
    _entity = EntityService::getInstance()->createEntity("MWell");
    _independentVariables = new MIndependentVariables{};
    _wellReservoirUnit = new WellReservoirUnit{};
}

void MWellItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {
    event->accept();
    if (event->button() != Qt::LeftButton) {
        return;
    }

    auto* bridge = new MSignalBridge{};
    gpQmlApplicationEngine->rootContext()->setContextProperty("bridge", bridge);
    gpQmlApplicationEngine->rootContext()->setContextProperty("well", QVariant::fromValue(_entity));
    gpQmlApplicationEngine->rootContext()->setContextProperty("independentVariables",
                                                              QVariant::fromValue(_independentVariables));
    gpQmlApplicationEngine->rootContext()->setContextProperty("calculationUnit",
                                                              QVariant::fromValue(_wellReservoirUnit));

    QObject::connect(bridge, &MSignalBridge::onDataChanged, [this](const QVariant& data) {
        /// Casting directly to MEntity* will produce nullptr,
        /// however, a middle step (QQmlPropertyMap*, aka MEntity's superclass)
        /// can get the valid pointer. 好奇怪啊
        auto* entityStep1 = data.value<QQmlPropertyMap*>();
        auto* entityStep2 = dynamic_cast<MEntity*>(entityStep1);
        // const auto* entity = data.value<MEntity*>(); // nullptr

        if (!entityStep2) {
            log_critical("Failed to cast QVariant to MEntity*");
            return;
        }
        if (_entity == entityStep2) {
            // 其实是同一份啦
            return;
        }
        _entity = entityStep2;
    });
    qml::navigate("/well-editor");
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
