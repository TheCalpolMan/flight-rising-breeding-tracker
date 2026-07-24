#include "modutils.h"

#include <cmath>

namespace ModUtils
{
int sign(double a)
{
    return a < 0 ? -1 : 1;
}

double absMin(double a, double b)
{
    if (std::fabs(a) < std::fabs(b))
    {
        return a;
    }

    return b;
}

double getDisplacement(double from, double to, int modulus)
{
    double d = to - from;

    return absMin(d, d - modulus * sign(d));
}

double getDistance(double from, double to, int modulus)
{
    double dx = std::fabs(to - from);

    return std::fmin(dx, modulus - dx);
}
}
