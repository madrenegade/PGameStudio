#include "Math/Quaternion.h"
#include <cmath>

namespace Math
{

    Quaternion::Quaternion(double x, double y, double z, double w)
        : m_axis(x, y, z), m_angle(w)
    {
        //ctor
    }

    Quaternion::Quaternion(const Math::Vector3& axis, double w)
        : m_axis(axis), m_angle(w)
    {

    }

    Quaternion::Quaternion(const Quaternion& q)
        : m_axis(q.m_axis), m_angle(q.m_angle)
    {

    }

    Quaternion::~Quaternion()
    {
        //dtor
    }

    Vector4 Quaternion::ToAxisAngle() const
    {
        Quaternion q(*this);

        if(q.m_angle > 1.0)
        {
            q.Normalize();
        }

        Vector4 result;
        result.W = 2.0 * std::acos(q.m_angle);

        double den = std::sqrt(1.0 - q.m_angle * q.m_angle);

        if (den > 0.0001)
        {
            result.X = q.m_axis.X / den;
            result.Y = q.m_axis.Y / den;
            result.Z = q.m_axis.Z / den;
        }
        else
        {
            // This occurs when the angle is zero.
            // Not a problem: just set an arbitrary normalized axis.
            result.X = 1;
            result.Y = 0;
            result.Z = 0;
        }

        return result;
    }

    Vector3 Quaternion::ToDirection() const
    {
        Quaternion q(*this);

        Quaternion qConjugate(q);
        qConjugate.Conjugate();

        Quaternion v(0, 1, 0, 0);

        Quaternion result(q * v * qConjugate);

        return result.m_axis;
    }

    Quaternion Quaternion::operator*(const Quaternion& rhs) const
    {
        return Quaternion(rhs.m_angle * this->m_axis + this->m_angle * rhs.m_axis + this->m_axis.Cross(rhs.m_axis),
                          this->m_angle * rhs.m_angle - this->m_axis.Dot(rhs.m_axis));
    }

    double Quaternion::Length() const
    {
        return std::sqrt(this->m_angle * this->m_angle + this->m_axis.LengthSquared());
    }

    Quaternion& Quaternion::Normalize()
    {
        double length = this->Length();

        this->m_axis /= length;
        this->m_angle /= length;

        return *this;
    }

    Quaternion& Quaternion::Conjugate()
    {
        this->m_axis = -this->m_axis;

        return *this;
    }

    Quaternion Quaternion::FromAxisAngle(const Vector3& a, double angle)
    {
        Vector3 axis(a);

        if (axis.LengthSquared() == 0.0)
        {
            return Quaternion(0, 0, 0, 1);
        }

        angle *= 0.5;
        axis.Normalize();

        Quaternion result(axis * std::sin(angle), std::cos(angle));
        result.Normalize();

        return result;
    }

    Vector3 Quaternion::GetAxis() const
    {
        return this->m_axis;
    }

    double Quaternion::Angle() const
    {
        return this->m_angle;
    }

} // namespace Math
