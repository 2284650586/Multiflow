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

    /**
     * @brief 这个函数会比预期的调用更频繁一些，比如每次输入框内容变动都会带来一次调用。
     * 所以这个函数不应该做太多事情～
     */
    void onUserDataSaved() const override;

    [[nodiscard]] bool canConnectWith(const MAbstractItem& other, ConnectionKind kind) const override;
};
