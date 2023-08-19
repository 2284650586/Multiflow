#include "tsinkitem.h"
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QPen>
#include <QStyleOptionGraphicsItem>
#include <parUI/sinkdialog.h>

TSinkItem::TSinkItem(QString sinkName, QGraphicsItem *parent) : QGraphicsPixmapItem(parent), sinkName(sinkName)
{
    QPixmap pixmap = QPixmap(":/image/sink.png");
    pixmap = pixmap.scaled(35, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setPixmap(pixmap);
    setFlags(GraphicsItemFlag::ItemIsMovable |
             GraphicsItemFlag::ItemIsSelectable |
             GraphicsItemFlag::ItemSendsGeometryChanges |
             GraphicsItemFlag::ItemIsFocusable);
}


QRectF TSinkItem::boundingRect() const
{
    QRect rect = pixmap().rect();
    return QRectF(0, 0, rect.width(), rect.height());
}

void TSinkItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    painter->drawText(0, 0, sinkName);
}

int TSinkItem::getId()
{
    return sink.getSourceId();
}

QString TSinkItem::getName()
{
    return sinkName;
}

QVariant TSinkItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        emit sinkItemChange();
    }
    return value;
}


void TSinkItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    sinkDialog *dialog = new sinkDialog();
    dialog->exec();
    delete dialog;
}
