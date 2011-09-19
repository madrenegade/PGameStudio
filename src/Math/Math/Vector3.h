#ifndef MATH_VECTOR3_H
#define MATH_VECTOR3_H

#include "math_defines.h"
#include <ostream>

namespace Math
{
    class MATH_EXPORT Vector3
    {
    public:
        Vector3(double x = 0, double y = 0, double z = 0);
        Vector3(const Vector3& v);
        ~Vector3();

        Vector3& operator/=(double value);
        Vector3& operator+=(const Vector3& rhs);
        Vector3& operator-=(const Vector3& rhs);

        Vector3 operator+(const Vector3& rhs) const;
        Vector3 operator-(const Vector3& rhs) const;
        Vector3 operator-() const;

        Vector3 operator*(double value) const;

        friend Vector3 operator*(double value, const Vector3& v);

        Vector3& Normalize();

        Vector3 Cross(const Vector3& rhs) const;
        double Dot(const Vector3& rhs) const;

        double Length() const;
        double LengthSquared() const;

        double X, Y, Z;
    };

} // namespace Math

template<class T>
std::ostream& operator <<(std::ostream& stream, const Math::Vector3& vector)
{
    stream << "v(" << vector.X() << " " << vector.Y() << " " << vector.Z() << ")";

    return stream;
}

#endif // MATH_VECTOR3_H
