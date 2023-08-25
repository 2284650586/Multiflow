#include "math.h"

#include <cmath>
#include <algorithm>
#include <stdexcept>

namespace math
{
double add(double x, double y)
{
    return x + y;
}

double subtract(double x, double y)
{
    return x - y;
}

double multiply(double x, double y)
{
    return x * y;
}

double divide(double x, double y)
{
    if (y == 0)
    {
        throw std::exception("Divide by zero.");
    }
    return x / y;
}

double power(double x, double y)
{
    return std::pow(x, y);
}

double square_root(double x)
{
    return std::sqrt(x);
}

double absolute_value(double x)
{
    return std::abs(x);
}

double sine(double x)
{
    return std::sin(x);
}

double cosine(double x)
{
    return std::cos(x);
}

double tangent(double x)
{
    return std::tan(x);
}

double arcsine(double x)
{
    return std::asin(x);
}

double arccosine(double x)
{
    return std::acos(x);
}

double arctangent(double x)
{
    return std::atan(x);
}

double logarithm(double base, double x)
{
    // 换底公式
    return std::log(x) / std::log(base);
}

double minimum(double x, double y)
{
    return std::min(x, y);
}

double maximum(double x, double y)
{
    return std::max(x, y);
}
}
