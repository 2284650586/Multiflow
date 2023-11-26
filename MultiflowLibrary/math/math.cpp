#include "math/math.hpp"

#include <cmath>
#include <algorithm>

namespace ml {
math_error::math_error(const char* what) : _what(what) {
}

const char* math_error::what() const noexcept {
    return _what;
}

#define ASSERT_VALID(x) \
    if (std::isnan(x) || std::isinf(x)) \
    { \
        throw math_error("数值非法，不可为NaN或无穷大"); \
    }

bool z(const double x) {
    ASSERT_VALID(x)
    return std::abs(x) < ZERO_THRESHOLD;
}

bool eq(const double x, const double y) {
    ASSERT_VALID(x)
    ASSERT_VALID(y)
    return z(x - y);
}

bool gt(const double x, const double y) {
    ASSERT_VALID(x)
    ASSERT_VALID(y)
    return x > y + ZERO_THRESHOLD;
}

bool lt(const double x, const double y) {
    ASSERT_VALID(x)
    ASSERT_VALID(y)
    return x < y - ZERO_THRESHOLD;
}

bool gte(const double x, const double y) {
    ASSERT_VALID(x)
    ASSERT_VALID(y)
    return gt(x, y) || eq(x, y);
}

bool lte(const double x, const double y) {
    ASSERT_VALID(x)
    ASSERT_VALID(y)
    return lt(x, y) || eq(x, y);
}

double add(const double x, const double y) {
    ASSERT_VALID(x)
    ASSERT_VALID(y)
    return x + y;
}

double subtract(const double x, const double y) {
    ASSERT_VALID(x)
    ASSERT_VALID(y)
    return x - y;
}

double multiply(const double x, const double y) {
    ASSERT_VALID(x)
    ASSERT_VALID(y)

    // 避免超大的数和带有误差的0相乘不等于0的情况
    if (z(x) || z(y)) {
        return CONST_ZERO;
    }
    return x * y;
}

double divide(const double x, const double y) {
    ASSERT_VALID(x)
    ASSERT_VALID(y)

    // 避免带有误差的0除以极小的数不等于0的情况
    if (z(x)) {
        return CONST_ZERO;
    }

    if (z(y)) {
        throw math_error("不可除以零");
    }
    return x / y;
}

double power(const double x, const double y) {
    ASSERT_VALID(x)
    ASSERT_VALID(y)

    if (lt(x, CONST_ZERO) && lt(y, 1)) {
        throw math_error("不可对负数开方");
    }
    return std::pow(x, y);
}

double square_root(const double x) {
    ASSERT_VALID(x)

    if (lt(x, CONST_ZERO)) {
        throw math_error("实数不可<0");
    }
    return std::sqrt(x);
}

double absolute_value(const double x) {
    ASSERT_VALID(x)
    return std::abs(x);
}

double logarithm(const double base, const double x) {
    ASSERT_VALID(base)
    ASSERT_VALID(x)

    if (lte(x, CONST_ZERO)) {
        throw math_error("实数不可<=0");
    }

    if (eq(base, 1) || lte(base, CONST_ZERO)) {
        throw math_error("底数不能为1或<=0");
    }

    // 自带的std::log不知道是什么底数
    // 用换底公式确保底数为base
    // 由于之前检查过base不为1，所以不用担心出现除0
    return divide(std::log(x), std::log(base));
}

double minimum(const double x, const double y) {
    ASSERT_VALID(x)
    ASSERT_VALID(y)
    return std::min(x, y);
}

double maximum(const double x, const double y) {
    ASSERT_VALID(x)
    ASSERT_VALID(y)
    return std::max(x, y);
}

double logical_and(const double x, const double y) {
    ASSERT_VALID(x)
    ASSERT_VALID(y)
    return !z(x) && !z(y) ? CONST_TRUE : CONST_FALSE;
}

double logical_or(const double x, const double y) {
    ASSERT_VALID(x)
    ASSERT_VALID(y)
    return !z(x) || !z(y) ? CONST_TRUE : CONST_FALSE;
}

bool is_logical_true(const double x) {
    ASSERT_VALID(x)
    return !z(x);
}
}
