//
// Created by miku on 11/17/2023.
//

#pragma once

#include "MAbstractItem.hpp"
#include "graphics_view/window/MWellDisplayWindow.hpp"

class MWellItem final : public MAbstractItem {
    MWellDisplayWindow* _wellDisplayWindow{};

public:
    explicit MWellItem(QGraphicsPixmapItem* parent = nullptr);

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

    void onUserDataSaved() const override;

    [[nodiscard]] bool canConnectWith(const MAbstractItem& other, ConnectionKind kind) const override;
};
