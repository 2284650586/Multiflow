//
// Created by miku on 11/17/2023.
//

#pragma once

#include "shared.hpp"
#include "MArrow.hpp"

#include <QGraphicsPixmapItem>

enum ConnectionKind {
    START_TO_END,
    END_TO_START
};

class MAbstractItem : public QGraphicsPixmapItem {
public:
    enum { Type = UserType + 1 };

    using ArrowType = MArrow<MAbstractItem>;

    explicit MAbstractItem(
        MultiflowKind kind,
        QString itemName,
        const QString& resourceFileName,
        QGraphicsPixmapItem* parent = nullptr
    );

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    [[nodiscard]] QRectF boundingRect() const override;

    [[nodiscard]] QPainterPath shape() const override;

    [[nodiscard]] const QString& itemName() const;

    [[nodiscard]] const QList<ArrowType*>& arrows() const;

    [[nodiscard]] MultiflowKind itemKind() const;

    [[nodiscard]] int type() const override;

    void addArrow(ArrowType* arrow);

    void removeArrow(const ArrowType* arrow);

    void removeAllArrows();

    void setItemName(const QString& name);

    [[nodiscard]] size_t countStartArrows() const;

    [[nodiscard]] size_t countEndArrows() const;

    [[nodiscard]] virtual bool canConnectWith(const MAbstractItem& other, ConnectionKind kind) const = 0;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

    QString _itemName{};
    QList<ArrowType*> _arrows{};
    MultiflowKind _kind;
};
