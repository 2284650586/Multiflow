#include "MGraphicsScene.hpp"

#include "shared.hpp"
#include "MAbstractItem.hpp"
#include "MSourceItem.hpp"
#include "MWellItem.hpp"
#include "MSinkItem.hpp"
#include "MJunctionItem.hpp"
#include "MArrow.hpp"

#include <MultiflowLibrary/logging/logging.hpp>

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QGraphicsItem>

#include "qml/utils/UIUtils.hpp"

constexpr QGraphicsSceneMouseEvent* EventNothing = nullptr;


MGraphicsScene::MGraphicsScene(QObject* parent)
    : QGraphicsScene{parent},
      _sceneMode(MoveItem) {
}

void MGraphicsScene::setMode(const Mode mode) {
    _sceneMode = mode;
}

void MGraphicsScene::setItemType(const MItemKind kind) {
    _itemKind = kind;
}

MAbstractItem* MGraphicsScene::_createItem(const MItemKind kind) {
    switch (kind) {
        case Well: return new MWellItem{};
        case Source: return new MSourceItem{};
        case Sink: return new MSinkItem{};
        case Junction: return new MJunctionItem{};
        default: throw ItemNotFoundException{"不存在这种类型的图元"};
    }
}

void MGraphicsScene::_handleInsertItem(const QGraphicsSceneMouseEvent* event) {
    MAbstractItem* item;
    try {
        item = _createItem(_itemKind);
    }
    catch (const ItemNotFoundException& e) {
        _handleSetPointer(EventNothing);
        UIUtils::error(e.what(), "好");
        return;
    }

    addItem(item);
    item->setPos(event->scenePos());
    update();
    log_info("Insert {} item at ({}, {})", item->itemName().toStdString(), event->scenePos().x(),
             event->scenePos().y());
    emit mulItemInserted(item);
}

void MGraphicsScene::_handleInsertLine(const QGraphicsSceneMouseEvent* event) {
    _line = new QGraphicsLineItem{
        QLineF{event->scenePos(), event->scenePos()}
    };
    _line->setPen(QPen(lineColor, 2));

    addItem(_line);
    update();
    emit linePointerInserted();
}

void MGraphicsScene::_handleSetPointer(const QGraphicsSceneMouseEvent* event) {
    Q_UNUSED(event)

    update();
    emit setPointerCursor();
}

void MGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() != Qt::LeftButton) {
        return;
    }

    switch (_sceneMode) {
        case InsertItem: {
            _handleInsertItem(event);
            break;
        }
        case InsertLine: {
            _handleInsertLine(event);
            break;
        }
        case SetPointer: {
            _handleSetPointer(event);
            break;
        }
        default:
            break;
    }
    QGraphicsScene::mousePressEvent(event);
}

void MGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    update();
    if (_sceneMode == InsertLine && _line != nullptr) {
        _line->setLine({_line->line().p1(), event->scenePos()});
    }
    else {
        QGraphicsScene::mouseMoveEvent(event);
    }
}

void MGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() != Qt::LeftButton) {
        return;
    }
    if (_line != nullptr && _sceneMode == InsertLine) {
        QList<QGraphicsItem*> startItems = items(_line->line().p1());
        QList<QGraphicsItem*> endItems = items(_line->line().p2());

        if (startItems.count() && startItems.first() == _line) {
            startItems.removeFirst();
        }
        if (endItems.count() && endItems.first() == _line) {
            endItems.removeFirst();
        }

        removeItem(_line);

        if (startItems.count() <= 0 || endItems.count() <= 0) {
            QGraphicsScene::mouseReleaseEvent(event);
            return;
        }

        if (startItems.first()->type() != MAbstractItem::Type || endItems.first()->type() != MAbstractItem::Type) {
            return;
        }

        if (startItems.first() == endItems.first()) {
            return;
        }

        auto* startItem = qgraphicsitem_cast<MAbstractItem*>(startItems.first());
        auto* endItem = qgraphicsitem_cast<MAbstractItem*>(endItems.first());

        if (canInterConnect(startItem, endItem)) {
            const auto arrow = new MAbstractItem::ArrowType{startItem, endItem};
            startItem->addArrow(arrow);
            endItem->addArrow(arrow);
            arrow->setZValue(-1000.0);
            addItem(arrow);
            arrow->updatePosition();
        }
    }
    _line = nullptr;
    QGraphicsScene::mouseReleaseEvent(event);
}

bool MGraphicsScene::isItemChange(const int type) const {
    return std::ranges::any_of(
        selectedItems(),
        [type](const QGraphicsItem* item) {
            return item->type() == type;
        }
    );
}

bool MGraphicsScene::canInterConnect(const MAbstractItem* startItem, const MAbstractItem* endItem) {
    return startItem->canConnectWith(*endItem, START_TO_END)
           && endItem->canConnectWith(*startItem, END_TO_START);
}
