#include "tgraphicsscene.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QGraphicsItem>
#include <QDebug>
#include "mulitem.h"
#include "tarrow.h"
#include "shared.hpp"

TGraphicsScene::TGraphicsScene(QObject *parent)
    : QGraphicsScene{parent}
{
    m_mode = MoveItem;
    line = nullptr;
}

TGraphicsScene::~TGraphicsScene()
{

}

void TGraphicsScene::setMode(Mode mode)
{
    m_mode = mode;
}

void TGraphicsScene::setItemType(MultiflowKind type)
{
    m_itemType = type;
}

void TGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }

    MulItem *item;
    switch(m_mode) {
    case InsertItem: {
        QString name = getName();
        item = new MulItem(m_itemType, name);
        addItem(item);
        item->setPos(event->scenePos());
        update();
        emit mulItemInserted(item);
        break;
    }
    case InsertLine: {
        line = new QGraphicsLineItem(QLineF(event->scenePos(), event->scenePos()));
        line->setPen(QPen(myLineColor, 2));
        addItem(line);
        update();
        emit linePointerInserted();
        break;
    }
    case setPointer: {
        update();
        emit setPointerCursor();
        break;
    }
    default:
        break;
    }

    QGraphicsScene::mousePressEvent(event);
}

void TGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    if (m_mode == InsertLine && line != nullptr) {
        QLineF newLine(line->line().p1(), event->scenePos());
        line->setLine(newLine);
    } else {
        QGraphicsScene::mouseMoveEvent(event);
    }
}

void TGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }
    if (line != nullptr && m_mode == InsertLine) {
        QList<QGraphicsItem*> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line) {
            startItems.removeFirst();
        }
        QList<QGraphicsItem*> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line) {
            endItems.removeFirst();
        }

        removeItem(line);
        delete line;

        if (startItems.count() <= 0 || endItems.count() <= 0) {
            QGraphicsScene::mouseReleaseEvent(event);
            return;
        }

        if (startItems.first()->type() != MulItem::Type || endItems.first()->type() != MulItem::Type) {
            return;
        }

        if (startItems.first() == endItems.first()) {
            return;
        }

        MulItem *startItem = qgraphicsitem_cast<MulItem *>(startItems.first());
        MulItem *endItem = qgraphicsitem_cast<MulItem *>(endItems.first());

        int flag = judgeConnect(startItem, endItem);

        if (flag) {
            TArrow *arrow = new TArrow(startItem, endItem);
            startItem->addArrow(arrow);
            endItem->addArrow(arrow);
            arrow->setZValue(-1000.0);
            addItem(arrow);
            arrow->updatePosition();
        }
    }
    line = nullptr;
    QGraphicsScene::mouseReleaseEvent(event);
}

bool TGraphicsScene::isItemChange(int type) const
{
    const QList<QGraphicsItem *> items = selectedItems();
    const auto cb = [type](const QGraphicsItem *item) { return item->type() == type; };
    return std::find_if(items.begin(), items.end(), cb) != items.end();
}

bool TGraphicsScene::judgeConnect(MulItem *startItem, MulItem *endItem)
{
    int flag = true;

    //判断能不能连接

    if (startItem->MulType() == MultiflowKind::Well) {
        if (startItem->getStartArrowNum() >= 1) flag = false;
        if (endItem->MulType() == MultiflowKind::Well) flag = false;
        if (endItem->MulType() == MultiflowKind::Source) flag = false;
    }

    if (startItem->MulType() == MultiflowKind::Source) {
        if (startItem->getStartArrowNum() >= 1) flag = false;
        if (endItem->MulType() == MultiflowKind::Well) flag = false;
        if (endItem->MulType() == MultiflowKind::Source) flag = false;
    }

    if (startItem->MulType() == MultiflowKind::Sink) {
        if (startItem->getStartArrowNum() >= 1) flag = false;
        if (endItem->MulType() == MultiflowKind::Sink) flag = false;
    }

    if (startItem->MulType() == MultiflowKind::Junction) flag = true;

    if (endItem->MulType() == MultiflowKind::Well) {
        if (endItem->getEndArrowNum() >= 1) flag = false;
        if (startItem->MulType() == MultiflowKind::Source) flag = false;
    }

    if (endItem->MulType() == MultiflowKind::Source) {
        if (endItem->getEndArrowNum() >= 1) flag = false;
        if (startItem->MulType() == MultiflowKind::Well) flag = false;
    }

    if (endItem->MulType() == MultiflowKind::Sink) {
        if (endItem->getEndArrowNum() >= 1) flag = false;
    }

    if (endItem->MulType() == MultiflowKind::Junction) flag = true;

    return flag;
}

QString TGraphicsScene::getName()
{
    if (m_itemType == MultiflowKind::Well) return QString("well");
    if (m_itemType == MultiflowKind::Source) return QString("source");
    if (m_itemType == MultiflowKind::Sink) return QString("sink");
    if (m_itemType == MultiflowKind::Junction) return QString("junction");
    return QString("未命名");
}
