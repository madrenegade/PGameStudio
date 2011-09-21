#ifndef MATH_VECTOR4_H
#define MATH_VECTOR4_H

#include "math_defines.h"
#include <ostream>

namespace Math
{
    class Vector3;
    class Matrix4;
    
    class MATH_EXPORT Vector4
    {
    public:
        Vector4(const Vector3& v, double w = 0);
        Vector4(double x = 0, double y = 0, double z = 0, double w = 0);
        ~Vector4();

        Vector4& operator/=(double value);
        Vector4& operator+=(const Vector4& rhs);
        Vector4& operator-=(const Vector4& rhs);
        
        Vector4& operator*=(const Matrix4& rhs);

        double Length() const;
        Vector4& Normalize();

        double X;
        double Y;
        double Z;
        double W;
    };

} // namespace Math

template<class T>
std::ostream& operator <<(std::ostream& stream, const Math::Vector4& vector)
{
    stream << "v(" << vector.X() << " " << vector.Y() << " " << vector.Z() << " " << vector.W << ")";

    return stream;
}

#endif // MATH_VECTOR4_H
