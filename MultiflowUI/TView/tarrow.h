#ifndef TARROW_H
#define TARROW_H

#include <QGraphicsLineItem>
#include "entity/mflowline.h"

class QGraphicsItem;
class MulItem;

class TArrow : public QGraphicsLineItem
{
public:
    enum { Type = UserType + 2};
    TArrow(MulItem *startItem, MulItem *endItem, QGraphicsItem *parent = nullptr);
    ~TArrow();

    int type() const override { return Type; }

    MulItem *getStartItem();
    MulItem *getEndItem();

    void updatePosition();

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    QPainterPath shape() const override;




    // QGraphicsItem interface
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    MulItem *startItem;
    MulItem *endItem;
    QPolygonF arrowHead;
    QColor myColor = Qt::black;

    QString name = "flowline";

//数据部分
private:
    MFlowline *flowline = nullptr;

    // QGraphicsItem interface
protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // TARROW_H
