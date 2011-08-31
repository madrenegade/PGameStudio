#ifndef MATH_VECTOR2_H
#define MATH_VECTOR2_H

#include "math_defines.h"

namespace Math
{

    class MATH_EXPORT Vector2
    {
    public:
        Vector2(double x = 0, double y = 0);
        ~Vector2();

        double X, Y;
    };

} // namespace Math

#endif // MATH_VECTOR2_H
