//
// Created by miku on 11/17/2023.
//

#pragma once

#include "MAbstractItem.hpp"
#include "..\entity\MWell.hpp"

class MWellItem final : public MAbstractItem {
public:
    explicit MWellItem(QGraphicsPixmapItem* parent = nullptr);

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

    [[nodiscard]] bool canConnectWith(const MAbstractItem& other, ConnectionKind kind) const override;

private:
    MWell* _well;
};
