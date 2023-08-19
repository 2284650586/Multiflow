#include "tarrow.h"
#include "TView/mulitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPen>
#include <QtMath>
#include <parUI/mflowlinedialog.h>

TArrow::TArrow(MulItem *startItem, MulItem *endItem, QGraphicsItem *parent)
    : QGraphicsLineItem(parent), startItem(startItem), endItem(endItem)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

TArrow::~TArrow()
{
    if (flowline != nullptr) {
        delete flowline;
    }
}

MulItem *TArrow::getStartItem()
{
    return startItem;
}

MulItem *TArrow::getEndItem()
{
    return endItem;
}

QRectF TArrow::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;
    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

QPainterPath TArrow::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}

void TArrow::updatePosition()
{
    QPointF startPoint = startItem->pos() + QPointF(startItem->boundingRect().width() / 2, startItem->boundingRect().height() / 2);
    QPointF endPoint = endItem->pos() + QPointF(endItem->boundingRect().width() / 2, endItem->boundingRect().height() / 2);

    QLineF line(startPoint, endPoint);
    setLine(line);
}


void TArrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (startItem->collidesWithItem(endItem)) {
        return;
    }

    QPen myPen = pen();
    myPen.setColor(myColor);
    qreal arrowSize = 10;
    myPen.setWidth(3);
    painter->setPen(myPen);
    painter->setBrush(myColor);

    QPointF startCenter = startItem->scenePos() + QPointF(startItem->boundingRect().width() / 2, startItem->boundingRect().height() / 2);
    QPointF endCenter = endItem->scenePos() + QPointF(endItem->boundingRect().width() / 2, endItem->boundingRect().height() / 2);

    QLineF centerLine(startCenter, endCenter);
    QPolygonF endPolygon = endItem->boundingRect();
    QPointF p1 = endPolygon.first() + endItem->pos();
    QPointF intersectPoint;
    for (int i = 1; i < endPolygon.count(); ++i) {
        QPointF p2 = endPolygon.at(i) + endItem->pos();
        QLineF polyLine = QLineF(p1, p2);
        QLineF::IntersectionType intersectionType =
            polyLine.intersects(centerLine, &intersectPoint);
        if (intersectionType == QLineF::BoundedIntersection)
            break;
        p1 = p2;
    }
    setLine(QLineF(intersectPoint, startCenter));
    double angle = std::atan2(-line().dy(), line().dx());

    QPointF midPoint = line().pointAt(0.5);

    QPointF arrowP1 = midPoint + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                         cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = midPoint + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                         cos(angle + M_PI - M_PI / 3) * arrowSize);

    arrowHead.clear();
    arrowHead << midPoint << arrowP1 << arrowP2;

    painter->drawLine(line());
    painter->drawPolygon(arrowHead);

    QPointF textPos = midPoint + QPointF(0, -20);
    painter->drawText(textPos, name);

    if (isSelected()) {
        painter->setPen(QPen(Qt::red, 1, Qt::SolidLine));
        QLineF myLine = line();
        myLine.translate(0, 4.0);
        painter->drawLine(myLine);
        myLine.translate(0,-8.0);
        painter->drawLine(myLine);
    }
    update();
}


void TArrow::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    bool isNew = false;
    if (event->button() == Qt::LeftButton)
    {
        if (flowline == nullptr) {
            isNew = true;
            flowline = new MFlowline();
        }
        MFlowlineDialog *dialog = new MFlowlineDialog(flowline, isNew, name);
        dialog->exec();
        if (name != dialog->getName()) {
            name = dialog->getName();
            update();
        }
        delete dialog;
    }
}

