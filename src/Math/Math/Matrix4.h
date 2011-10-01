#ifndef MATH_MATRIX4_H
#define MATH_MATRIX4_H

#include "math_defines.h"

#ifdef DEBUG
#include <string>
#endif

#include <vector>

#include "Math/Vector3.h"
#include "Math/Quaternion.h"

namespace Math
{
    class MATH_EXPORT Matrix4
    {
    public:
        Matrix4();
        Matrix4(const double* const d);

        Matrix4(double m11, double m12, double m13, double m14,
                double m21, double m22, double m23, double m24,
                double m31, double m32, double m33, double m34,
                double m41, double m42, double m43, double m44);

        Matrix4(const Matrix4& m);
        ~Matrix4();

        Matrix4& operator = (const Matrix4& rhs);

        Matrix4 operator*(const Matrix4& rhs) const;

        operator const double*() const;

        Matrix4& Transpose();

        static Matrix4 CreatePerspectiveFieldOfView(double fieldOfView, double aspect, double near, double far);
        static Matrix4 LookAt(const Vector3& position, const Vector3& lookAt, const Vector3& up);

        static Matrix4 CreateTranslation(const Vector3& translation);
        static Matrix4 CreateRotation(const Quaternion& rotation);
        static Matrix4 Scale(const Vector3& scale);
        static Matrix4 CreateTransform(const Vector3& translation = Vector3(0, 0, 0),
                                       const Quaternion& rotation = Quaternion(),
                                       const Vector3& scale = Vector3(1, 1, 1));

        static Matrix4 CreateShearing(double s);

        double m11;
        double m12;
        double m13;
        double m14;

        double m21;
        double m22;
        double m23;
        double m24;

        double m31;
        double m32;
        double m33;
        double m34;

        double m41;
        double m42;
        double m43;
        double m44;
    };

} // namespace Math

std::ostream& operator <<(std::ostream& stream, const Math::Matrix4& m);

#endif // MATH_MATRIX4_H
