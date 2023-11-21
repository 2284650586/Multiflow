//
// Created by miku on 11/17/2023.
//

#pragma once

#include "MAbstractItem.hpp"
#include "entity/MSource.hpp"

class MSourceItem final : public MAbstractItem {
public:
    explicit MSourceItem(QGraphicsPixmapItem* parent = nullptr);

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

    [[nodiscard]] bool canConnectWith(const MAbstractItem& other, ConnectionKind kind) const override;

private:
    MSource* _source{};
};
