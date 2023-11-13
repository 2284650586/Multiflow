#ifndef MULITEM_H
#define MULITEM_H

#include "shared.hpp"
#include "entity/msink.h"
#include "entity/msource.h"
#include "entity/mwell.h"
#include "entity/mjunction.h"
#include "TView/tarrow.h"
#include "parUI/mwellwindow.h"


class MulItem : public QGraphicsPixmapItem {
public:
    enum { Type = UserType + 1 };


    MulItem(MultiflowKind type, QString itemName, QGraphicsPixmapItem* parent = nullptr);

    ~MulItem();

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    QPainterPath shape() const override;


    int type() const override { return Type; }
    int MulType() const { return mulType; }

    void addArrow(TArrow* arrow);

    void removeArrow(TArrow* arrow);

    void removeArrows();

    void setItemName(QString name) { itemName = name; }
    QString getItemName() { return itemName; }

    int getArrowNum() { return arrows.count(); }

    int getStartArrowNum();

    int getEndArrowNum();

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

private:
    QString itemName;
    QList<TArrow*> arrows;
    MultiflowKind mulType;

    void handleItemName(QString name);


    //数据部分
private:
    MWell* well;
    MSource* source;
    MSink* sink;
    MJunction* junction;

private:
    MWellWindow* mWindow = nullptr;

    // QGraphicsItem interface
protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // MULITEM_H
