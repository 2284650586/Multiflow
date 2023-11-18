#include "MGraphicsScene.hpp"

#include "shared.hpp"
#include "MAbstractItem.hpp"
#include "MSourceItem.hpp"
#include "MWellItem.hpp"
#include "MSinkItem.hpp"
#include "MJunctionItem.hpp"
#include "MArrow.hpp"
#include "utils/type_utils.hpp"

#include <MultiflowLibrary/logging/logging.hpp>

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QGraphicsItem>

MGraphicsScene::MGraphicsScene(QObject* parent)
    : QGraphicsScene{parent},
      _sceneMode(MoveItem) {
}

void MGraphicsScene::setMode(const Mode mode) {
    _sceneMode = mode;
}

void MGraphicsScene::setItemType(const MultiflowKind kind) {
    _itemKind = kind;
}

void MGraphicsScene::_handleInsertItem(const QGraphicsSceneMouseEvent* event) {
    std::shared_ptr<MAbstractItem> item{};
    switch (_itemKind) {
        case Well:
            item = std::make_shared<MWellItem>();
            break;

        case Source:
            item = std::make_shared<MSourceItem>();
            break;

        case Sink:
            item = std::make_shared<MSinkItem>();
            break;

        case Junction:
            item = std::make_shared<MJunctionItem>();
            break;

        default:
            return;
    }
    addItem(item.get());
    item->setPos(event->scenePos());
    update();
    emit mulItemInserted(item.get());
}

void MGraphicsScene::_handleInsertLine(const QGraphicsSceneMouseEvent* event) {
    _line = std::make_shared<QGraphicsLineItem>(
        QLineF{event->scenePos(), event->scenePos()});
    _line->setPen(QPen(lineColor, 2));

    addItem(_line.get());
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
        case setPointer: {
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
    if (_sceneMode != InsertLine || _line == nullptr) {
        return;
    }

    QList<QGraphicsItem*> startItemPtrs = items(_line->line().p1());
    QList<QGraphicsItem*> endItemsPtrs = items(_line->line().p2());
    QList<std::shared_ptr<QGraphicsItem>> startItems{};
    QList<std::shared_ptr<QGraphicsItem>> endItems{};

    std::ranges::transform(startItemPtrs, std::back_inserter(startItems), [](QGraphicsItem* item) {
        return std::shared_ptr<QGraphicsItem>(item);
    });
    std::ranges::transform(endItemsPtrs, std::back_inserter(endItems), [](QGraphicsItem* item) {
        return std::shared_ptr<QGraphicsItem>(item);
    });

    if (startItems.count() && startItems.first() == _line) {
        startItems.removeFirst();
    }
    if (endItems.count() && endItems.first() == _line) {
        endItems.removeFirst();
    }

    removeItem(_line.get());
    _line = nullptr;

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

    std::shared_ptr<MAbstractItem> startItem = ml::as<MAbstractItem>(startItems.first());
    std::shared_ptr<MAbstractItem> endItem = ml::as<MAbstractItem>(endItems.first());

    if (!ml::instance_of<MAbstractItem>(startItems.first())) {
        log_error("startItems.first() is not MItem! 实在是太惨了");
    }

    if (judgeConnect(startItem, endItem)) {
        const auto arrow = std::make_shared<MAbstractItem::ArrowType>(startItem, endItem);
        startItem->addArrow(arrow);
        endItem->addArrow(arrow);
        arrow->setZValue(-1000.0);
        arrow->updatePosition();
        addItem(arrow.get());
    }

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

bool MGraphicsScene::judgeConnect(
    const std::shared_ptr<MAbstractItem>& startItem,
    const std::shared_ptr<MAbstractItem>& endItem
) {
    return startItem->canConnectWith(*endItem, START_TO_END)
           && endItem->canConnectWith(*startItem, END_TO_START);
}

QString MGraphicsScene::name() const {
    switch (_itemKind) {
        case Well:
            return "Well";

        case Source:
            return "Source";

        case Sink:
            return "Sink";

        case Junction:
            return "Junction";

        default:
            return "未命名";
    }
}
