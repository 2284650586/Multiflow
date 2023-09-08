#ifndef TFLOWLINEITEM_H
#define TFLOWLINEITEM_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "entity/msource.h"
#include "common.h"

class TFlowlineItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum { Type = UserType + MultiflowKind::Flowline };

    TFlowlineItem(QString flowlineName = "flowline", QGraphicsItem *parent = nullptr);

private:
    QString flowlineName;
    MSource flowline;

public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QString getId();
    QString getName();

    int type() const override { return Type; }

signals:
    void flowItemChange();

    // QGraphicsItem interface
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    // QGraphicsItem interface
protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // TFLOWLINEITEM_H
