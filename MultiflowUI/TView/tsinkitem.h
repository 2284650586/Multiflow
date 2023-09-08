#ifndef TSINKITEM_H
#define TSINKITEM_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "entity/msource.h"
#include "common.h"

class TSinkItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum { Type = UserType + MultiflowKind::Sink };
    TSinkItem(QString sinkName = "sink", QGraphicsItem *parent = nullptr);

private:
    QString sinkName;
    MSource sink;

public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QString getId();
    QString getName();

    int type() const override { return Type; }

signals:
    void sinkItemChange();

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    // QGraphicsItem interface
protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // TSINKITEM_H
