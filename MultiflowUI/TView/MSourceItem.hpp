//
// Created by miku on 11/17/2023.
//

#pragma once

#include "MAbstractItem.hpp"
#include "entity/msource.h"

class MSourceItem final : public MAbstractItem {
    Q_OBJECT

public:
    explicit MSourceItem(QGraphicsPixmapItem* parent = nullptr);

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

    [[nodiscard]] bool canConnectWith(const MAbstractItem& other, ConnectionKind kind) const override;

private:
    std::shared_ptr<MSource> _source{};
};
