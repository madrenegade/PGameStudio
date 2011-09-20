#include "Math/Matrix4.h"
#include <cmath>

#ifdef DEBUG
#include <cassert>
#include <sstream>
#endif

namespace Math
{
#ifdef CXX0X_INITIALIZER_LISTS

    Matrix4::Matrix4()
    : m_values({
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    })
    {
    }
#else

    Matrix4::Matrix4(double m11, double m12, double m13, double m14,
                     double m21, double m22, double m23, double m24,
                     double m31, double m32, double m33, double m34,
                     double m41, double m42, double m43, double m44)
    : m_values(16)
    {
        this->m_values[0] = m11;
        this->m_values[1] = m12;
        this->m_values[2] = m13;
        this->m_values[3] = m14;
        this->m_values[4] = m21;
        this->m_values[5] = m22;
        this->m_values[6] = m23;
        this->m_values[7] = m24;
        this->m_values[8] = m31;
        this->m_values[9] = m32;
        this->m_values[10] = m33;
        this->m_values[11] = m34;
        this->m_values[12] = m41;
        this->m_values[13] = m42;
        this->m_values[14] = m43;
        this->m_values[15] = m44;
    }
#endif

    Matrix4::Matrix4(const double* const d)
#ifdef CXX0X_INITIALIZER_LISTS
    : m_values({
        d[0], d[1], d[2], d[3],
        d[4], d[5], d[6], d[7],
        d[8], d[9], d[10], d[11],
        d[12], d[13], d[14], d[15]
    })
#else
    : m_values(16)
#endif
    {
#ifndef CXX0X_INITIALIZER_LISTS
        for (unsigned int i = 0; i < 16; ++i)
        {
            this->m_values[i] = d[i];
        }
#endif
    }

#ifdef CXX0X_INITIALIZER_LISTS

    Matrix4::Matrix4(std::initializer_list<double> d)
    : m_values(d)
    {
    }
#endif

    Matrix4::Matrix4(const Matrix4& m)
    : m_values(m.m_values)
    {
    }

    Matrix4::~Matrix4()
    {
        //dtor
    }

    Matrix4& Matrix4::operator =(const Matrix4& rhs)
    {
        this->m_values = rhs.m_values;

        return *this;
    }

    Matrix4 Matrix4::operator*(const Matrix4& rhs) const
    {
        return Matrix4(
#ifdef CXX0X_INITIALIZER_LISTS
        {
#endif
            this->M11() * rhs.M11() + this->M12() * rhs.M21() + this->M13() * rhs.M31() + this->M14() * rhs.M41(),
            this->M11() * rhs.M12() + this->M12() * rhs.M22() + this->M13() * rhs.M32() + this->M14() * rhs.M42(),
            this->M11() * rhs.M13() + this->M12() * rhs.M23() + this->M13() * rhs.M33() + this->M14() * rhs.M43(),
            this->M11() * rhs.M14() + this->M12() * rhs.M24() + this->M13() * rhs.M34() + this->M14() * rhs.M44(),
            this->M21() * rhs.M11() + this->M22() * rhs.M21() + this->M23() * rhs.M31() + this->M24() * rhs.M41(),
            this->M21() * rhs.M12() + this->M22() * rhs.M22() + this->M23() * rhs.M32() + this->M24() * rhs.M42(),
            this->M21() * rhs.M13() + this->M22() * rhs.M23() + this->M23() * rhs.M33() + this->M24() * rhs.M43(),
            this->M21() * rhs.M14() + this->M22() * rhs.M24() + this->M23() * rhs.M34() + this->M24() * rhs.M44(),
            this->M31() * rhs.M11() + this->M32() * rhs.M21() + this->M33() * rhs.M31() + this->M34() * rhs.M41(),
            this->M31() * rhs.M12() + this->M32() * rhs.M22() + this->M33() * rhs.M32() + this->M34() * rhs.M42(),
            this->M31() * rhs.M13() + this->M32() * rhs.M23() + this->M33() * rhs.M33() + this->M34() * rhs.M43(),
            this->M31() * rhs.M14() + this->M32() * rhs.M24() + this->M33() * rhs.M34() + this->M34() * rhs.M44(),
            this->M41() * rhs.M11() + this->M42() * rhs.M21() + this->M43() * rhs.M31() + this->M44() * rhs.M41(),
            this->M41() * rhs.M12() + this->M42() * rhs.M22() + this->M43() * rhs.M32() + this->M44() * rhs.M42(),
            this->M41() * rhs.M13() + this->M42() * rhs.M23() + this->M43() * rhs.M33() + this->M44() * rhs.M43(),
            this->M41() * rhs.M14() + this->M42() * rhs.M24() + this->M43() * rhs.M34() + this->M44() * rhs.M44()
#ifdef CXX0X_INITIALIZER_LISTS
        }
#endif
        );
    }

    Matrix4::operator const double*() const
    {
        return &this->m_values[0];
    }
    
    Matrix4& Matrix4::Transpose()
    {
        const Matrix4 temp(*this);
        
        this->M11(temp.M11());
        this->M12(temp.M21());
        this->M13(temp.M31());
        this->M14(temp.M41());
        
        this->M21(temp.M12());
        this->M22(temp.M22());
        this->M23(temp.M32());
        this->M24(temp.M42());
        
        this->M31(temp.M13());
        this->M32(temp.M23());
        this->M33(temp.M33());
        this->M34(temp.M43());
        
        this->M41(temp.M14());
        this->M42(temp.M24());
        this->M43(temp.M34());
        this->M44(temp.M44());
        
        return *this;
    }

    Matrix4 Matrix4::CreatePerspectiveFieldOfView(double fieldOfView, double aspect, double near, double far)
    {
        double yMax = near * std::tan(0.5 * fieldOfView);
        double yMin = -yMax;
        double xMin = yMin * aspect;
        double xMax = yMax * aspect;

        double x = (2.0 * near) / (xMax - xMin);
        double y = (2.0 * near) / (yMax - yMin);
        double a = (xMax + xMin) / (xMax - xMin);
        double b = (yMax + yMin) / (yMax - yMin);
        double c = -(far + near) / (far - near);
        double d = -(2.0 * far * near) / (far - near);

        return Matrix4(
#ifdef CXX0X_INITIALIZER_LISTS
        {
#endif
            x, 0, 0, 0,
            0, y, 0, 0,
            a, b, c, -1,
            0, 0, d, 0
#ifdef CXX0X_INITIALIZER_LISTS
        }
#endif
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
#ifdef CXX0X_INITIALIZER_LISTS
        {
#endif
            x.X, y.X, z.X, 0,
            x.Y, y.Y, z.Y, 0,
            x.Z, y.Z, z.Z, 0,
            0, 0, 0, 1
#ifdef CXX0X_INITIALIZER_LISTS
        }
#endif
        );

        return Matrix4::CreateTranslation(-position).Transpose() * rot;
    }

    Matrix4 Matrix4::CreateTranslation(const Vector3& translation)
    {
        return Matrix4(
#ifdef CXX0X_INITIALIZER_LISTS
        {
#endif
            //            1, 0, 0, 0,
            //            0, 1, 0, 0,
            //            0, 0, 1, 0,
            //            translation.X, translation.Y, translation.Z, 1
            1, 0, 0, translation.X,
            0, 1, 0, translation.Y,
            0, 0, 1, translation.Z,
            0, 0, 0, 1
#ifdef CXX0X_INITIALIZER_LISTS
        }
#endif
        );
    }

    Matrix4 Matrix4::CreateRotation(const Quaternion& rotation)
    {
        Vector4 axisAngle = rotation.ToAxisAngle();

        Vector3 axis(axisAngle.X, axisAngle.Y, axisAngle.Z);
        axis.Normalize();

        double angle = axisAngle.W;

        double cos = std::cos(-angle);
        double sin = std::sin(-angle);
        double t = 1.0 - cos;

        return Matrix4(
#ifdef CXX0X_INITIALIZER_LISTS
        {
#endif
            t * axis.X * axis.X + cos, t * axis.X * axis.Y - sin * axis.Z, t * axis.X * axis.Z + sin * axis.Y, 0.0,
            t * axis.X * axis.Y + sin * axis.Z, t * axis.Y * axis.Y + cos, t * axis.Y * axis.Z - sin * axis.X, 0.0,
            t * axis.X * axis.Z - sin * axis.Y, t * axis.Y * axis.Z + sin * axis.X, t * axis.Z * axis.Z + cos, 0.0,
            0, 0, 0, 1
#ifdef CXX0X_INITIALIZER_LISTS
        }
#endif
        );
    }

    Matrix4 Matrix4::Scale(const Vector3& scale)
    {
        return Matrix4(
#ifdef CXX0X_INITIALIZER_LISTS
        {
#endif
            scale.X, 0, 0, 0,
            0, scale.Y, 0, 0,
            0, 0, scale.Z, 0,
            0, 0, 0, 1
#ifdef CXX0X_INITIALIZER_LISTS
        }
#endif
        );
    }

    Matrix4 Matrix4::CreateTransform(const Vector3& translation, const Quaternion& rotation, const Vector3& scale)
    {
        return Scale(scale) * CreateTranslation(translation) * CreateRotation(rotation);
    }

    Matrix4 Matrix4::CreateShearing(double s)
    {
        return Matrix4(
#ifdef CXX0X_INITIALIZER_LISTS
        {
#endif
            1, 0, s, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
#ifdef CXX0X_INITIALIZER_LISTS
        }
#endif
        );
    }

#ifdef DEBUG

    Matrix4::operator std::string() const
    {
        std::stringstream s;
        s << this->M11();
        s << " ";
        s << this->M12();
        s << " ";
        s << this->M13();
        s << " ";
        s << this->M14();
        s << std::endl;
        s << this->M21();
        s << " ";
        s << this->M22();
        s << " ";
        s << this->M23();
        s << " ";
        s << this->M24();
        s << std::endl;
        s << this->M31();
        s << " ";
        s << this->M32();
        s << " ";
        s << this->M33();
        s << " ";
        s << this->M34();
        s << std::endl;
        s << this->M41();
        s << " ";
        s << this->M42();
        s << " ";
        s << this->M43();
        s << " ";
        s << this->M44();
        s << std::endl;

        return s.str();
    }
#endif

    double Matrix4::M11() const
    {
        return this->m_values[0];
    }

    double Matrix4::M12() const
    {
        return this->m_values[1];
    }

    double Matrix4::M13() const
    {
        return this->m_values[2];
    }

    double Matrix4::M14() const
    {
        return this->m_values[3];
    }

    double Matrix4::M21() const
    {
        return this->m_values[4];
    }

    double Matrix4::M22() const
    {
        return this->m_values[5];
    }

    double Matrix4::M23() const
    {
        return this->m_values[6];
    }

    double Matrix4::M24() const
    {
        return this->m_values[7];
    }

    double Matrix4::M31() const
    {
        return this->m_values[8];
    }

    double Matrix4::M32() const
    {
        return this->m_values[9];
    }

    double Matrix4::M33() const
    {
        return this->m_values[10];
    }

    double Matrix4::M34() const
    {
        return this->m_values[11];
    }

    double Matrix4::M41() const
    {
        return this->m_values[12];
    }

    double Matrix4::M42() const
    {
        return this->m_values[13];
    }

    double Matrix4::M43() const
    {
        return this->m_values[14];
    }

    double Matrix4::M44() const
    {
        return this->m_values[15];
    }

    void Matrix4::M11(double m)
    {
        this->m_values[0] = m;
    }

    void Matrix4::M12(double m)
    {
        this->m_values[1] = m;
    }

    void Matrix4::M13(double m)
    {
        this->m_values[2] = m;
    }

    void Matrix4::M14(double m)
    {
        this->m_values[3] = m;
    }

    void Matrix4::M21(double m)
    {
        this->m_values[4] = m;
    }

    void Matrix4::M22(double m)
    {
        this->m_values[5] = m;
    }

    void Matrix4::M23(double m)
    {
        this->m_values[6] = m;
    }

    void Matrix4::M24(double m)
    {
        this->m_values[7] = m;
    }

    void Matrix4::M31(double m)
    {
        this->m_values[8] = m;
    }

    void Matrix4::M32(double m)
    {
        this->m_values[9] = m;
    }

    void Matrix4::M33(double m)
    {
        this->m_values[10] = m;
    }

    void Matrix4::M34(double m)
    {
        this->m_values[11] = m;
    }

    void Matrix4::M41(double m)
    {
        this->m_values[12] = m;
    }

    void Matrix4::M42(double m)
    {
        this->m_values[13] = m;
    }

    void Matrix4::M43(double m)
    {
        this->m_values[14] = m;
    }

    void Matrix4::M44(double m)
    {
        this->m_values[15] = m;
    }

} // namespace Math
