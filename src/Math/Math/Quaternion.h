#ifndef MATH_QUATERNION_H
#define MATH_QUATERNION_H

#include "Math/Vector3.h"
#include "Math/Vector4.h"

namespace Math
{

    class MATH_EXPORT Quaternion
    {
    public:
        Quaternion(double x = 0, double y = 0, double z = 0, double w = 1);
        Quaternion(const Math::Vector3& axis, double w);
        Quaternion(const Quaternion& q);
        ~Quaternion();

        Vector4 ToAxisAngle() const;
        Vector3 ToDirection() const;

        Quaternion operator*(const Quaternion& rhs) const;

        double Length() const;
        Quaternion& Normalize();

        Quaternion& Conjugate();

        static Quaternion FromAxisAngle(const Vector3& axis, double angle);

        Vector3 GetAxis() const;
        double Angle() const;

    private:
        Vector3 m_axis;
        double m_angle;
    };

} // namespace Math

#endif // MATH_QUATERNION_H
