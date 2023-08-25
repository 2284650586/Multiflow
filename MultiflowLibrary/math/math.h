#ifndef MATH_H
#define MATH_H

#include "../MultiflowLibrary_global.h"

namespace math
{

ML_PUBLIC double add(double x, double y);
ML_PUBLIC double subtract(double x, double y);
ML_PUBLIC double multiply(double x, double y);
ML_PUBLIC double divide(double x, double y);
ML_PUBLIC double power(double x, double y);
ML_PUBLIC double square_root(double x);
ML_PUBLIC double absolute_value(double x);
ML_PUBLIC double sine(double x);
ML_PUBLIC double cosine(double x);
ML_PUBLIC double tangent(double x);
ML_PUBLIC double arcsine(double x);
ML_PUBLIC double arccosine(double x);
ML_PUBLIC double arctangent(double x);
ML_PUBLIC double logarithm(double base, double x);
ML_PUBLIC double minimum(double x, double y);
ML_PUBLIC double maximum(double x, double y);

}

#endif // MATH_H
