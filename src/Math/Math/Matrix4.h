#ifndef MATH_MATRIX4_H
#define MATH_MATRIX4_H

#include "math_defines.h"

#ifdef DEBUG
#include <string>
#endif

#include <vector>

#ifdef CXX0X_INITIALIZER_LISTS
#include <initializer_list>
#endif

#include "Math/Vector3.h"
#include "Math/Quaternion.h"

namespace Math
{

    class MATH_EXPORT Matrix4
    {
    public:
        Matrix4();
        Matrix4(const double* const d);

#ifdef CXX0X_INITIALIZER_LISTS
        Matrix4(std::initializer_list<double> d);
#else
        Matrix4(double m11, double m12, double m13, double m14,
                double m21, double m22, double m23, double m24,
                double m31, double m32, double m33, double m34,
                double m41, double m42, double m43, double m44);
#endif

        Matrix4(const Matrix4& m);
        ~Matrix4();

        Matrix4& operator = (const Matrix4& rhs);

        Matrix4 operator*(const Matrix4& rhs) const;

        operator const double*() const;
        
        Matrix4& Transpose();


#ifdef DEBUG
        operator std::string() const;
#endif

        double M11() const;
        double M12() const;
        double M13() const;
        double M14() const;

        double M21() const;
        double M22() const;
        double M23() const;
        double M24() const;

        double M31() const;
        double M32() const;
        double M33() const;
        double M34() const;

        double M41() const;
        double M42() const;
        double M43() const;
        double M44() const;

        void M11(double m);
        void M12(double m);
        void M13(double m);
        void M14(double m);

        void M21(double m);
        void M22(double m);
        void M23(double m);
        void M24(double m);

        void M31(double m);
        void M32(double m);
        void M33(double m);
        void M34(double m);

        void M41(double m);
        void M42(double m);
        void M43(double m);
        void M44(double m);

        static Matrix4 CreatePerspectiveFieldOfView(double fieldOfView, double aspect, double near, double far);
        static Matrix4 LookAt(const Vector3& position, const Vector3& lookAt, const Vector3& up);

        static Matrix4 CreateTranslation(const Vector3& translation);
        static Matrix4 CreateRotation(const Quaternion& rotation);
        static Matrix4 Scale(const Vector3& scale);
        static Matrix4 CreateTransform(const Vector3& translation = Vector3(0, 0, 0),
                                       const Quaternion& rotation = Quaternion(),
                                       const Vector3& scale = Vector3(1, 1, 1));
        
        static Matrix4 CreateShearing(double s);

    private:
        std::vector<double> m_values;
    };

} // namespace Math

#endif // MATH_MATRIX4_H
