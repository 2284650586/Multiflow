//
// Created by miku on 11/17/2023.
//

#pragma once

#include "MAbstractItem.hpp"
#include "entity/msink.h"

class MSinkItem final : public MAbstractItem {
public:
    explicit MSinkItem(QGraphicsPixmapItem* parent = nullptr);

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

    [[nodiscard]] bool canConnectWith(const MAbstractItem& other, ConnectionKind kind) const override;

private:
    MSink* _sink{};
};
