#include "Math/Matrix4.h"
#include <cmath>

#ifdef DEBUG
#include <cassert>
#include <sstream>
#endif

namespace Math
{

    Matrix4::Matrix4()
    : m11(1), m12(0), m13(0), m14(0),
    m21(0), m22(1), m23(0), m24(0),
    m31(0), m32(0), m33(1), m34(0),
    m41(0), m42(0), m43(0), m44(1)
    {
    }

    Matrix4::Matrix4(double m11, double m12, double m13, double m14,
                     double m21, double m22, double m23, double m24,
                     double m31, double m32, double m33, double m34,
                     double m41, double m42, double m43, double m44)
    : m11(m11), m12(m12), m13(m13), m14(m14),
    m21(m21), m22(m22), m23(m23), m24(m24),
    m31(m31), m32(m32), m33(m33), m34(m34),
    m41(m41), m42(m42), m43(m43), m44(m44)
    {
    }

    Matrix4::Matrix4(const double* const d)
    : m11(d[0]), m12(d[1]), m13(d[2]), m14(d[3]),
    m21(d[4]), m22(d[5]), m23(d[6]), m24(d[7]),
    m31(d[8]), m32(d[9]), m33(d[10]), m34(d[11]),
    m41(d[12]), m42(d[13]), m43(d[14]), m44(d[15])
    {
    }

    Matrix4::Matrix4(const Matrix4& m)
    : m11(m.m11), m12(m.m12), m13(m.m13), m14(m.m14),
    m21(m.m21), m22(m.m22), m23(m.m23), m24(m.m24),
    m31(m.m31), m32(m.m32), m33(m.m33), m34(m.m34),
    m41(m.m41), m42(m.m42), m43(m.m43), m44(m.m44)
    {
    }

    Matrix4::~Matrix4()
    {
    }

    Matrix4& Matrix4::operator =(const Matrix4& rhs)
    {
        m11 = rhs.m11;
        m12 = rhs.m12;
        m13 = rhs.m13;
        m14 = rhs.m14;

        m21 = rhs.m21;
        m22 = rhs.m22;
        m23 = rhs.m23;
        m24 = rhs.m24;

        m31 = rhs.m31;
        m32 = rhs.m32;
        m33 = rhs.m33;
        m34 = rhs.m34;

        m41 = rhs.m41;
        m42 = rhs.m42;
        m43 = rhs.m43;
        m44 = rhs.m44;

        return *this;
    }

    Matrix4 Matrix4::operator*(const Matrix4& rhs) const
    {
        return Matrix4(
            m11 * rhs.m11 + m12 * rhs.m21 + m13 * rhs.m31 + m14 * rhs.m41,
            m11 * rhs.m12 + m12 * rhs.m22 + m13 * rhs.m32 + m14 * rhs.m42,
            m11 * rhs.m13 + m12 * rhs.m23 + m13 * rhs.m33 + m14 * rhs.m43,
            m11 * rhs.m14 + m12 * rhs.m24 + m13 * rhs.m34 + m14 * rhs.m44,
            m21 * rhs.m11 + m22 * rhs.m21 + m23 * rhs.m31 + m24 * rhs.m41,
            m21 * rhs.m12 + m22 * rhs.m22 + m23 * rhs.m32 + m24 * rhs.m42,
            m21 * rhs.m13 + m22 * rhs.m23 + m23 * rhs.m33 + m24 * rhs.m43,
            m21 * rhs.m14 + m22 * rhs.m24 + m23 * rhs.m34 + m24 * rhs.m44,
            m31 * rhs.m11 + m32 * rhs.m21 + m33 * rhs.m31 + m34 * rhs.m41,
            m31 * rhs.m12 + m32 * rhs.m22 + m33 * rhs.m32 + m34 * rhs.m42,
            m31 * rhs.m13 + m32 * rhs.m23 + m33 * rhs.m33 + m34 * rhs.m43,
            m31 * rhs.m14 + m32 * rhs.m24 + m33 * rhs.m34 + m34 * rhs.m44,
            m41 * rhs.m11 + m42 * rhs.m21 + m43 * rhs.m31 + m44 * rhs.m41,
            m41 * rhs.m12 + m42 * rhs.m22 + m43 * rhs.m32 + m44 * rhs.m42,
            m41 * rhs.m13 + m42 * rhs.m23 + m43 * rhs.m33 + m44 * rhs.m43,
            m41 * rhs.m14 + m42 * rhs.m24 + m43 * rhs.m34 + m44 * rhs.m44);
    }

    Matrix4::operator const double*() const
    {
        return &m11;
    }

    Matrix4& Matrix4::Transpose()
    {
        const Matrix4 temp(*this);

        m11 = temp.m11;
        m12 = temp.m21;
        m13 = temp.m31;
        m14 = temp.m41;

        m21 = temp.m12;
        m22 = temp.m22;
        m23 = temp.m32;
        m24 = temp.m42;

        m31 = temp.m13;
        m32 = temp.m23;
        m33 = temp.m33;
        m34 = temp.m43;

        m41 = temp.m14;
        m42 = temp.m24;
        m43 = temp.m34;
        m44 = temp.m44;

        return *this;
    }

    Matrix4 Matrix4::CreatePerspectiveFieldOfView(double fieldOfView, double aspect, double near, double far)
    {
        const double yMax = near * std::tan(0.5 * fieldOfView);
        const double yMin = -yMax;
        const double xMin = yMin * aspect;
        const double xMax = yMax * aspect;

        const double x = (2.0 * near) / (xMax - xMin);
        const double y = (2.0 * near) / (yMax - yMin);
        const double a = (xMax + xMin) / (xMax - xMin);
        const double b = (yMax + yMin) / (yMax - yMin);
        const double c = -(far + near) / (far - near);
        const double d = -(2.0 * far * near) / (far - near);

        return Matrix4(
            x, 0, 0, 0,
            0, y, 0, 0,
            a, b, c, -1,
            0, 0, d, 0
            );
    }

    Matrix4 Matrix4::LookAt(const Vector3& position, const Vector3& lookAt, const Vector3& up)
    {
        Vector3 z(position - lookAt);
        z.Normalize();

        Vector3 x(up.Cross(z));
        x.Normalize();

        Vector3 y(z.Cross(x));
        y.Normalize();

        Matrix4 rot(
            x.X, y.X, z.X, 0,
            x.Y, y.Y, z.Y, 0,
            x.Z, y.Z, z.Z, 0,
            0, 0, 0, 1
            );

        return Matrix4::CreateTranslation(-position).Transpose() * rot;
    }

    Matrix4 Matrix4::CreateTranslation(const Vector3& translation)
    {
        return Matrix4(
            1, 0, 0, translation.X,
            0, 1, 0, translation.Y,
            0, 0, 1, translation.Z,
            0, 0, 0, 1
            );
    }

    Matrix4 Matrix4::CreateRotation(const Quaternion& rotation)
    {
        Vector4 axisAngle = rotation.ToAxisAngle();

        Vector3 axis(axisAngle.X, axisAngle.Y, axisAngle.Z);

        if(axis.LengthSquared() != 0)
        {
            axis.Normalize();
        }

        double angle = axisAngle.W;

        double cos = std::cos(-angle);
        double sin = std::sin(-angle);
        double t = 1.0 - cos;

        return Matrix4(
            t * axis.X * axis.X + cos, t * axis.X * axis.Y - sin * axis.Z, t * axis.X * axis.Z + sin * axis.Y, 0.0,
            t * axis.X * axis.Y + sin * axis.Z, t * axis.Y * axis.Y + cos, t * axis.Y * axis.Z - sin * axis.X, 0.0,
            t * axis.X * axis.Z - sin * axis.Y, t * axis.Y * axis.Z + sin * axis.X, t * axis.Z * axis.Z + cos, 0.0,
            0, 0, 0, 1
            );
    }

    Matrix4 Matrix4::Scale(const Vector3& scale)
    {
        return Matrix4(
            scale.X, 0, 0, 0,
            0, scale.Y, 0, 0,
            0, 0, scale.Z, 0,
            0, 0, 0, 1
            );
    }

    Matrix4 Matrix4::CreateTransform(const Vector3& translation, const Quaternion& rotation, const Vector3& scale)
    {
        return Scale(scale) * CreateTranslation(translation) * CreateRotation(rotation);
    }

    Matrix4 Matrix4::CreateShearing(double s)
    {
        return Matrix4(
            1, 0, s, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
            );
    }
} // namespace Math

std::ostream& operator <<(std::ostream& stream, const Math::Matrix4& m)
{
    stream << "M(" << std::endl
    << m.m11 << " \t" << m.m12 << " \t" << m.m13 << " \t" << m.m14 << std::endl
    << m.m21 << " \t" << m.m22 << " \t" << m.m23 << " \t" << m.m24 << std::endl
    << m.m31 << " \t" << m.m32 << " \t" << m.m33 << " \t" << m.m34 << std::endl
    << m.m41 << " \t" << m.m42 << " \t" << m.m43 << " \t" << m.m44 << ")";

    return stream;
}
