#include "twellitem.h"
#include <QPainter>
#include <QPen>
#include <QStyleOptionGraphicsItem>
#include "parUI/sinkdialog.h"

TWellItem::TWellItem(QString wellName, QGraphicsItem *parent) : QGraphicsPixmapItem(parent), wellName(wellName)
{
    QPixmap pixmap = QPixmap(":/image/Well.png");
    pixmap = pixmap.scaled(30, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setPixmap(pixmap);
    setFlags(GraphicsItemFlag::ItemIsMovable |
             GraphicsItemFlag::ItemIsSelectable |
             GraphicsItemFlag::ItemSendsGeometryChanges |
             GraphicsItemFlag::ItemIsFocusable);
}


QRectF TWellItem::boundingRect() const
{
    QRect rect = pixmap().rect();
    return QRectF(0, 0, rect.width(), rect.height());
}

void TWellItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::TextAntialiasing);
    QPixmap pixmap = this->pixmap();
    QRect rect = pixmap.rect();
//    QRect newRect = QRect(0, 0, rect.width() + 30, rect.width() + 30);

    painter->drawPixmap(rect, pixmap);

    QPen pen(Qt::black);
    painter->setPen(pen);
    QFont font("Verdana", 8, QFont::Normal);
    painter->setFont(font);
    //painter->drawText(QRectF(0, rect.height(), rect.width() + 20, 15), Qt::AlignCenter, wellName);
    painter->drawText(0, 0, wellName);
}

int TWellItem::getId()
{
    return well.getSourceId();
}

QString TWellItem::getName()
{
    return wellName;
}


QVariant TWellItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        emit wellItemChange();
    }
    return value;
}


void TWellItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    sinkDialog *dialog = new sinkDialog();
    dialog->exec();
    delete dialog;
}
