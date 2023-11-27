//
// Created by miku on 11/17/2023.
//

#pragma once

#include "shared.hpp"
#include "MArrow.hpp"

#include "entity/unit/WellCalculationUnit.hpp"
#include "entity/MEntity.hpp"
#include "entity/MIndependentVariables.hpp"
#include "qml/bridge/MSignalBridge.hpp"

#include <QQuickWindow>

enum ConnectionKind {
    START_TO_END,
    END_TO_START
};

class MAbstractItem : public QGraphicsPixmapItem {
public:
    using ArrowType = MArrow<MAbstractItem>;

protected:
    MEntity* _entity{};
    MIndependentVariables* _independentVariables{};
    MSignalBridge* _bridge{};
    AbstractCalculationUnit* _calculationUnit{};
    QString _itemName{};
    QString _qmlRoute{};
    QList<ArrowType*> _arrows{};
    MItemKind _kind;

    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

    // NOLINTNEXTLINE
    QQuickWindow* openEditorDialog(const QString& route) const;

    virtual void onUserDataSaved() const = 0;

public:
    enum { Type = UserType + 1 };

    explicit MAbstractItem(
        MItemKind kind,
        QString itemName,
        const QString& resourceFileName,
        QString route,
        MEntity* entity,
        AbstractCalculationUnit* calculationUnit,
        QGraphicsPixmapItem* parent = nullptr
    );

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    [[nodiscard]] QRectF boundingRect() const override;

    [[nodiscard]] QPainterPath shape() const override;

    [[nodiscard]] const QString& itemName() const;

    [[nodiscard]] const QList<ArrowType*>& arrows() const;

    [[nodiscard]] MItemKind itemKind() const;

    [[nodiscard]] int type() const override;

    void addArrow(ArrowType* arrow);

    void removeArrow(const ArrowType* arrow);

    void removeAllArrows();

    void setItemName(const QString& name);

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

    [[nodiscard]] size_t countStartArrows() const;

    [[nodiscard]] size_t countEndArrows() const;

    [[nodiscard]] virtual bool canConnectWith(const MAbstractItem& other, ConnectionKind kind) const = 0;
};
