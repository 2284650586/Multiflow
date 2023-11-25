//
// Created by Hatsune Miku on 2023-11-23.
//

#pragma once

#include "qml/mixin/SingletonMixin.hpp"

// 有一个就够了吧
class CoordinateHelper final : public SingletonMixin<CoordinateHelper> {
    friend class SingletonMixin;
    int _width{0};
    int _height{0};

public:
    explicit CoordinateHelper() = default;

    ~CoordinateHelper() = default;

    void updateBoundaries(int width, int height);

    /**
     * @brief left(0.2) = 大约从左到右20%
     */
    [[nodiscard]] double left(double percent) const;

    /**
     * @brief top(0.2) = 大约从上到下20%
     */
    [[nodiscard]] double top(double percent) const;

    /**
     * @brief hcenter(0.2) = 大约横向正中间但是偏右20%
     */
    [[nodiscard]] double hcenter(double offsetPercent) const;

    /**
     * @brief vcenter(0.2) = 大约纵向正中间但是偏下20%
     */
    [[nodiscard]] double vcenter(double offsetPercent) const;
};
