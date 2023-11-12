#pragma once

#include <stdexcept>

/**
 * @brief 基本数学操作。包含了一系列保护措施，
 * 遇到各种非法操作会抛出异常
 * 遇到NaN和Infinite也会抛出异常
 *
 * @author z
 */
namespace ml
{

class  __declspec(dllexport) math_error : public std::exception {
private:
    const char* _what;
public:
    explicit math_error(const char* what);
    const char* what() const override;
};

constexpr double TRUE = 1;
constexpr double FALSE = 0;
constexpr double ZERO = 0;

/**
 * @brief 判断x是否为零，兼容IEEE浮点数的误差
 */
 __declspec(dllexport) bool z(double x);

/**
 * @brief 判断两数是否相等，兼容IEEE浮点数的误差
 */
 __declspec(dllexport) bool eq(double x, double y);

/**
 * @brief 判断x是否大于y，兼容IEEE浮点数的误差
 */
 __declspec(dllexport) bool gt(double x, double y);

/**
 * @brief 判断x是否小于y，兼容IEEE浮点数的误差
 */
 __declspec(dllexport) bool lt(double x, double y);

/**
 * @brief 判断x是否大于等于y，兼容IEEE浮点数的误差
 */
 __declspec(dllexport) bool gte(double x, double y);

/**
 * @brief 判断x是否小于等于y，兼容IEEE浮点数的误差
 */
 __declspec(dllexport) bool lte(double x, double y);

/**
 * @brief 加法，不带溢出检测
 */
 __declspec(dllexport) double add(double x, double y);

/**
 * @brief 减法，不带溢出检测
 */
 __declspec(dllexport) double subtract(double x, double y);

/**
 * @brief 乘法，不带溢出检测
 * 能够正确处理误差0和无穷大的情况
 */
 __declspec(dllexport) double multiply(double x, double y);

/**
 * @brief 除法，不带溢出检测
 * 能够正确处理被除数是误差0、出现无穷大的情况
 * 遇到除以0会抛出异常
 */
 __declspec(dllexport) double divide(double x, double y);

/**
 * @brief 幂函数，不带溢出检测
 * 遇到对负数开方会抛出异常，即使有时候负数开方也是能开的
 */
 __declspec(dllexport) double power(double x, double y);

/**
 * @brief 平方根，遇到负数会抛出异常
 */
 __declspec(dllexport) double square_root(double x);

/**
 * @brief 绝对值
 */
 __declspec(dllexport) double absolute_value(double x);

/**
 * @brief 对数函数，不带溢出检测，遇到以下情况会抛出异常：
 * base <= 0,
 * base == 1, 或
 * x <= 0
 */
 __declspec(dllexport) double logarithm(double base, double x);

/**
 * @brief 取较小值
 */
 __declspec(dllexport) double minimum(double x, double y);

/**
 * @brief 取较大值
 */
 __declspec(dllexport) double maximum(double x, double y);

/**
 * @brief 逻辑与，要求x和y同时在浮点数意义上不为零
 */
double logical_and(double x, double y);

/**
 * @brief 逻辑或，要求x或y至少有一个在浮点数意义上不为零
 */
double logical_or(double x, double y);

/**
 * @brief 如果x在浮点数意义上不等于零，返回1，否则返回0
 */
double is_logical_true(double x);

}
