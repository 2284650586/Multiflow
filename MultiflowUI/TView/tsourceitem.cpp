#include "tsourceitem.h"
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QPen>
#include <QStyleOptionGraphicsItem>
#include <parUI/sinkdialog.h>

TSourceItem::TSourceItem(QString sourceName, QGraphicsItem *parent) : QGraphicsPixmapItem(parent), sourceName(sourceName)
{
    QPixmap pixmap = QPixmap(":/resources/image/source.png");
    pixmap = pixmap.scaled(30, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setPixmap(pixmap);
    setFlags(GraphicsItemFlag::ItemIsMovable |
             GraphicsItemFlag::ItemIsSelectable |
             GraphicsItemFlag::ItemSendsGeometryChanges |
             GraphicsItemFlag::ItemIsFocusable);
}


QRectF TSourceItem::boundingRect() const
{
    QRect rect = pixmap().rect();
    return QRectF(0, 0, rect.width(), rect.height());
}

void TSourceItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap = this->pixmap();
    QRect rect = pixmap.rect();
    //    QRect newRect = QRect(0, 0, rect.width() + 30, rect.width() + 30);

    painter->drawPixmap(rect, pixmap);

    QPen pen(Qt::black);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
    QFont font("Verdana", 8, QFont::Normal);
    painter->setFont(font);
    //painter->drawText(QRectF(0, rect.height(), rect.width() + 20, 30), Qt::AlignCenter, sourceName);
    painter->drawText(0, 0, sourceName);
}

int TSourceItem::getId()
{
    return source.getSourceId();
}

QString TSourceItem::getName()
{
    return sourceName;
}


QVariant TSourceItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        emit sourceItemChange();
    }
    return value;
}

void TSourceItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    sinkDialog *dialog = new sinkDialog();
    dialog->exec();
    delete dialog;
}
