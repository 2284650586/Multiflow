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

class MAbstractItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    enum { Type = UserType + 1 };
    using ArrowType = MArrow<MAbstractItem>;

    explicit MAbstractItem(
        MultiflowKind kind,
        const QString& resourceFileName,
        QGraphicsPixmapItem* parent = nullptr
    );

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    [[nodiscard]] QRectF boundingRect() const override;

    [[nodiscard]] QPainterPath shape() const override;

    [[nodiscard]] const QString& itemName() const;

    [[nodiscard]] const QList<std::shared_ptr<ArrowType>>& arrows() const;

    [[nodiscard]] MultiflowKind itemKind() const;

    [[nodiscard]] int type() const override;

    void addArrow(const std::shared_ptr<ArrowType>& arrow);

    void removeArrow(const std::shared_ptr<ArrowType>& arrow);

    void removeAllArrows();

    void setItemName(const QString& name);

    [[nodiscard]] size_t countStartArrows() const;

    [[nodiscard]] size_t countEndArrows() const;

    [[nodiscard]] virtual bool canConnectWith(const MAbstractItem& other, ConnectionKind kind) const = 0;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

    QString _itemName{};
    QList<std::shared_ptr<ArrowType>> _arrows{};
    MultiflowKind _kind;
};
