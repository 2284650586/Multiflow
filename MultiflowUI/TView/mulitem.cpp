#include "mulitem.h"
#include "TView/tarrow.h"
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <parUI/mjunctiondialog.h>
#include <parUI/msinkdialog.h>
#include <parUI/msourcedialog.h>
#include <parUI/mwellwindow.h>


MulItem::MulItem(MultiflowKind type, QString itemName, QGraphicsPixmapItem *parent) :
    QGraphicsPixmapItem(parent), itemName(itemName)
{
    mulType = type;
    QPixmap pixmap = QPixmap();
    if (type == MultiflowKind::Well) {
        pixmap.load(":/resources/image/Well.png");
    } else if (type == MultiflowKind::Source) {
        pixmap.load(":/resources/image/source.png");
    } else if (type == MultiflowKind::Sink) {
        pixmap.load(":/resources/image/sink.png");
    } else if (type == MultiflowKind::Junction) {
        pixmap.load(":/resources/image/junction.png");
    }

    QPixmap myPixmap = pixmap.scaled(30, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    setPixmap(myPixmap);

    setFlags(GraphicsItemFlag::ItemIsMovable |
             GraphicsItemFlag::ItemIsSelectable |
             GraphicsItemFlag::ItemSendsGeometryChanges |
             GraphicsItemFlag::ItemIsFocusable);


    well = nullptr;
    source = nullptr;
    sink = nullptr;
    junction = nullptr;
}

MulItem::~MulItem()
{
    if (well != nullptr) {
        delete well;
        well = nullptr;
    }
    if (source != nullptr) {
        delete source;
        source = nullptr;
    }
    if (sink != nullptr) {
        delete sink;
        sink = nullptr;
    }
    if (junction != nullptr) {
        delete junction;
        junction = nullptr;
    }
    if (mWindow != nullptr) {
        delete mWindow;
        mWindow = nullptr;
    }

    removeArrows();
}

void MulItem::removeArrow(TArrow *arrow)
{
    arrows.removeAll(arrow);
}

void MulItem::removeArrows()
{
    const auto arrowsCopy = arrows;
    for (TArrow *arrow : arrowsCopy) {
        arrow->getStartItem()->removeArrow(arrow);
        arrow->getEndItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

int MulItem::getStartArrowNum()
{
    int count = 0;
    for (TArrow *arrow : arrows) {
        if (arrow->getStartItem() == this) {
            count++;
        }
    }
    return count;
}

int MulItem::getEndArrowNum()
{
    int count = 0;
    for (TArrow *arrow : arrows) {
        if (arrow->getEndItem() == this) {
            count++;
        }
    }
    return count;
}

void MulItem::addArrow(TArrow *arrow)
{
    arrows.append(arrow);
}


QRectF MulItem::boundingRect() const
{
    QRect rect = pixmap().rect();
    return QRectF(0, 0, rect.width(), rect.height());
}

void MulItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    painter->drawText(0, 0, itemName);

    if (isSelected()) {
        QPen pen(Qt::red);
        pen.setWidth(2);
        painter->setPen(pen);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(boundingRect());
    }

}

QVariant MulItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        for (TArrow *arrow : qAsConst(arrows))
            arrow->updatePosition();
    }

    return QGraphicsPixmapItem::itemChange(change, value);
}

void MulItem::handleItemName(QString name)
{
    itemName = name;
    update();
}

QPainterPath MulItem::shape() const
{
    QRectF rect = boundingRect();

    QPainterPath path;
    path.addRoundedRect(rect, 5, 5);
    return path;
}

void MulItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    bool isNew = false;
    if (event->button() == Qt::LeftButton)
    {
        if (mulType == MultiflowKind::Source) {
            if (source == nullptr) {
                isNew = true;
                source = new MSource();
            }
            MSourceDialog *dialog = new MSourceDialog(source, isNew, itemName);
            dialog->exec();
            if (itemName != dialog->getName()) {
                itemName = dialog->getName();
                update();
            }
            delete dialog;
        }

        if (mulType == MultiflowKind::Sink) {
            if (sink == nullptr) {
                isNew = true;
                sink = new MSink();
            }
            MSinkDialog *dialog = new MSinkDialog(sink, isNew, itemName);
            dialog->exec();
            if (itemName != dialog->getName()) {
                itemName = dialog->getName();
                update();
            }
            delete dialog;
        }

        if (mulType == MultiflowKind::Junction) {
            if (junction == nullptr) {
                isNew = true;
                junction = new MJunction();
            }
            MJunctionDialog *dialog = new MJunctionDialog(junction, isNew, itemName);
            dialog->exec();
            if (itemName != dialog->getName()) {
                itemName = dialog->getName();
                update();
            }
            delete dialog;
        }

        if (mulType == MultiflowKind::Well) {
            if (well == nullptr) well = new MWell();
            if (mWindow == nullptr) {
                mWindow = new MWellWindow(well, itemName);
                QObject::connect(mWindow, &MWellWindow::itemNameChange, [&](QString name) {
                    handleItemName(name);
                });
            }
            mWindow->show();
        }

    }

    event->accept();
}
