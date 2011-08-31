#include "Math/math_defines.h"

namespace Math
{
    double DegreesToRadians(double degrees)
    {
        const double degToRad = PI / 180.0;
        return degrees * degToRad;
    }

    double RadiansToDegrees(double radians)
    {
        const double radToDeg = 180.0 / PI;
        return radians * radToDeg;
    }
}
