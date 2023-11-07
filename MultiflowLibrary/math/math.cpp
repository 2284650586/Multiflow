#include "math/math.hpp"

#include <cmath>

namespace ml {
constexpr double ZERO_THRESHOLD = 1e-5;

math_error::math_error(const char* what) : _what(what) {
}

const char* math_error::what() const {
    return _what;
}

#define ASSERT_VALID(x) \
    if (std::isnan(x) || std::isinf(x)) \
    { \
        throw math_error("数值非法，不可为NaN或无穷大"); \
    }

bool z(double x) {
    ASSERT_VALID(x)
    return std::abs(x) < ZERO_THRESHOLD;
}

bool eq(double x, double y) {
    ASSERT_VALID(x)
    ASSERT_VALID(y)
    return z(x - y);
}

bool gt(double x, double y) {
    ASSERT_VALID(x)
    ASSERT_VALID(y)
    return x > y + ZERO_THRESHOLD;
}

bool lt(double x, double y) {
    ASSERT_VALID(x)
    ASSERT_VALID(y)
    return x < y - ZERO_THRESHOLD;
}

bool gte(double x, double y) {
    ASSERT_VALID(x)
    ASSERT_VALID(y)
    return gt(x, y) || eq(x, y);
}

bool lte(double x, double y) {
    ASSERT_VALID(x)
    ASSERT_VALID(y)
    return lt(x, y) || eq(x, y);
}

double add(double x, double y) {
    ASSERT_VALID(x)
    ASSERT_VALID(y)
    return x + y;
}

double subtract(double x, double y) {
    ASSERT_VALID(x)
    ASSERT_VALID(y)
    return x - y;
}

double multiply(double x, double y) {
    ASSERT_VALID(x)
    ASSERT_VALID(y)

    // 避免超大的数和带有误差的0相乘不等于0的情况
    if (z(x) || z(y)) {
        return 0;
    }
    return x * y;
}

double divide(double x, double y) {
    ASSERT_VALID(x)
    ASSERT_VALID(y)

    // 避免带有误差的0除以极小的数不等于0的情况
    if (z(x)) {
        return 0;
    }

    if (z(y)) {
        throw math_error("不可除以0");
    }
    return x / y;
}

double power(double x, double y) {
    ASSERT_VALID(x)
    ASSERT_VALID(y)

    if (lt(x, 0) && lt(y, 1)) {
        throw math_error("不可对负数开方");
    }
    return std::pow(x, y);
}

double square_root(double x) {
    ASSERT_VALID(x)

    if (lt(x, 0)) {
        throw math_error("实数不可<0");
    }
    return std::sqrt(x);
}

double absolute_value(double x) {
    ASSERT_VALID(x)
    return std::abs(x);
}

double logarithm(double base, double x) {
    ASSERT_VALID(base)
    ASSERT_VALID(x)

    if (x <= 0) {
        throw math_error("实数不可<=0");
    }

    if (eq(base, 1) || lte(base, 0)) {
        throw math_error("底数不能为1或<=0");
    }

    // 自带的std::log不知道是什么底数
    // 用换底公式确保底数为base
    // 由于之前检查过base不为1，所以不用担心出现除0
    return divide(std::log(x), std::log(base));
}

double minimum(double x, double y) {
    ASSERT_VALID(x)
    ASSERT_VALID(y)
    return std::min(x, y);
}

double maximum(double x, double y) {
    ASSERT_VALID(x)
    ASSERT_VALID(y)
    return std::max(x, y);
}

}
