//
// Created by miku on 11/17/2023.
//

#pragma once

#include "MAbstractItem.hpp"
#include "..\entity\MJunction.hpp"

class MJunctionItem final : public MAbstractItem {
public:
    explicit MJunctionItem(QGraphicsPixmapItem* parent = nullptr);

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

    [[nodiscard]] bool canConnectWith(const MAbstractItem& other, ConnectionKind kind) const override;

private:
    MJunction* _junction{};
};
