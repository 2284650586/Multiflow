#pragma once

#include "entity/mflowline.h"
#include "parUI/mflowlinedialog.h"

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

constexpr qreal ArrowSize = 10;

template<class ItemType>
class MArrow final : public QGraphicsLineItem {

public:
    enum { Type = UserType + 2 };

    explicit MArrow(
        std::shared_ptr<ItemType> startItem,
        std::shared_ptr<ItemType> endItem,
        QWidget* parent = nullptr
    ): _startItem(startItem), _endItem(endItem), _flowline(std::make_shared<MFlowline>()), _parent(parent) {
        setFlag(ItemIsSelectable, true);
        setPen(QPen{_arrowColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin});
    }

    ~MArrow() override = default;

    [[nodiscard]] int type() const override { return Type; }

    std::shared_ptr<ItemType> getStartItem() {
        return _startItem;
    }

    std::shared_ptr<ItemType> getEndItem() {
        return _endItem;
    }

    void updatePosition() {
        const QPointF startPoint =
            _startItem->pos() + QPointF{
                _startItem->boundingRect().width() / 2, _startItem->boundingRect().height() / 2
            };
        const QPointF endPoint =
            _endItem->pos() + QPointF{
                _endItem->boundingRect().width() / 2, _endItem->boundingRect().height() / 2
            };
        setLine({startPoint, endPoint});
    }

    [[nodiscard]] QRectF boundingRect() const override {
        const qreal extra = (pen().width() + 20) / 2.0;
        const auto size = QSizeF{
            line().p2().x() - line().p1().x(),
            line().p2().y() - line().p1().y()
        };
        return QRectF{line().p1(), size}
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
    }

    [[nodiscard]] QPainterPath shape() const override {
        QPainterPath path = QGraphicsLineItem::shape();
        path.addPolygon(_arrowHead);
        return path;
    }

protected:
    /**
     * @brief TODO: 这个算法太高深了
     */
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override {
        Q_UNUSED(option)
        Q_UNUSED(widget)

        if (_startItem->collidesWithItem(_endItem.get())) {
            return;
        }

        QPen myPen = pen();
        myPen.setColor(_arrowColor);
        myPen.setWidth(3);
        painter->setPen(myPen);
        painter->setBrush(_arrowColor);

        const QPointF startCenter =
            _startItem->scenePos() + QPointF(
                _startItem->boundingRect().width() / 2,
                _startItem->boundingRect().height() / 2);

        const QPointF endCenter =
            _endItem->scenePos() + QPointF(
                _endItem->boundingRect().width() / 2,
                _endItem->boundingRect().height() / 2);

        const QLineF centerLine{startCenter, endCenter};

        QPolygonF endPolygon = _endItem->boundingRect();
        QPointF p1 = endPolygon.first() + _endItem->pos();
        QPointF intersectPoint{};
        for (int i = 1; i < endPolygon.count(); ++i) {
            QPointF p2 = endPolygon.at(i) + _endItem->pos();
            if (QLineF{p1, p2}.intersects(centerLine, &intersectPoint) == QLineF::BoundedIntersection) {
                break;
            }
            p1 = p2;
        }
        setLine(QLineF{intersectPoint, startCenter});
        const double angle = std::atan2(-line().dy(), line().dx());

        const QPointF midPoint = line().pointAt(0.5);

        const QPointF arrowP1 =
            midPoint + QPointF{
                sin(angle + M_PI / 3) * ArrowSize,
                cos(angle + M_PI / 3) * ArrowSize
            };
        const QPointF arrowP2 =
            midPoint + QPointF{
                sin(angle + M_PI - M_PI / 3) * ArrowSize,
                cos(angle + M_PI - M_PI / 3) * ArrowSize
            };

        _arrowHead.clear();
        _arrowHead << midPoint << arrowP1 << arrowP2;

        painter->drawLine(line());
        painter->drawPolygon(_arrowHead);

        const QPointF textPos = midPoint + QPointF{0, -20};
        painter->drawText(textPos, _name);

        if (isSelected()) {
            painter->setPen(QPen(Qt::red, 1, Qt::SolidLine));
            QLineF myLine = line();

            myLine.translate(0, 4.0);
            painter->drawLine(myLine);

            myLine.translate(0, -8.0);
            painter->drawLine(myLine);
        }
        update();
    }

private:
    std::shared_ptr<ItemType> _startItem{};
    std::shared_ptr<ItemType> _endItem{};
    std::shared_ptr<MFlowline> _flowline{};
    QPolygonF _arrowHead{};
    QWidget* _parent{};

    QColor _arrowColor = Qt::black;
    QString _name = "Flowline";

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override {
        if (event->button() != Qt::LeftButton) {
            return;
        }

        auto* dialog = new MFlowlineDialog(_flowline, _name, _parent);
        dialog->exec();
        update();
    }
};
