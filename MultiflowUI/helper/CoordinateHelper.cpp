//
// Created by Hatsune Miku on 2023-11-23.
//

#include "CoordinateHelper.hpp"

void CoordinateHelper::updateBoundaries(const int width, const int height) {
    _width = width;
    _height = height;
}

double CoordinateHelper::left(const double percent) const {
    return percent * _width;
}

double CoordinateHelper::top(const double percent) const {
    return percent * _height;
}

double CoordinateHelper::hcenter(const double offsetPercent) const {
    return (0.5 + offsetPercent) * _width;
}

double CoordinateHelper::vcenter(const double offsetPercent) const {
    return offsetPercent * _height;
}
