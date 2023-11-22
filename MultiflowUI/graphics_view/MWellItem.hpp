//
// Created by miku on 11/17/2023.
//

#pragma once

#include "MAbstractItem.hpp"

class MWellItem final : public MAbstractItem {
public:
    explicit MWellItem(QGraphicsPixmapItem* parent = nullptr);

    void onUserDataSaved() const override;

    [[nodiscard]] bool canConnectWith(const MAbstractItem& other, ConnectionKind kind) const override;
};
