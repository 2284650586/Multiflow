#ifndef TSOURCEITEM_H
#define TSOURCEITEM_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "entity/msource.h"
#include "common.h"

class TSourceItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum { Type = UserType + MultiflowKind::Source };
    TSourceItem(QString sourceName = "source", QGraphicsItem *parent = nullptr);

    // QGraphicsItem interfac

private:
    MSource source;
    QString sourceName;

public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QString getId();
    QString getName();

    int type() const override { return Type; }

signals:
    void sourceItemChange();


    // QGraphicsItem interface
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    // QGraphicsItem interface
protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // TSOURCEITEM_H
