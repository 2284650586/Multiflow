#ifndef TWELLITEM_H
#define TWELLITEM_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "entity/msource.h"
#include "common.h"

class TWellItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum { Type = UserType + MultiflowKind::Well };
    TWellItem(QString wellName = "well", QGraphicsItem *parent = nullptr);

private:
    QString wellName;
    MSource well;

public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    int getId();
    QString getName();

    int type() const override { return Type; }

signals:
    void wellItemChange();


    // QGraphicsItem interface
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    // QGraphicsItem interface
protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // TWELLITEM_H
