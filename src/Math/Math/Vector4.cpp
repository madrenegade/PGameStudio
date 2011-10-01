#include "Math/Vector4.h"
#include "Matrix4.h"
#include <cmath>

namespace Math
{

    Vector4::Vector4(const Vector3& v, double w)
        : X(v.X), Y(v.Y), Z(v.Z), W(w)
    {

    }

    Vector4::Vector4(double x, double y, double z, double w)
        : X(x), Y(y), Z(z), W(w)
    {
        //ctor
    }

    Vector4::~Vector4()
    {
        //dtor
    }

    Vector4& Vector4::operator /=(double value)
    {
        this->X /= value;
        this->Y /= value;
        this->Z /= value;
        this->W /= value;

        return *this;
    }

    Vector4& Vector4::operator+=(const Vector4& rhs)
    {
        this->X += rhs.X;
        this->Y += rhs.Y;
        this->Z += rhs.Z;
        this->W += rhs.W;

        return *this;
    }

    Vector4& Vector4::operator-=(const Vector4& rhs)
    {
        this->X -= rhs.X;
        this->Y -= rhs.Y;
        this->Z -= rhs.Z;
        this->W -= rhs.W;

        return *this;
    }

    Vector4& Vector4::operator*=(const Matrix4& rhs)
    {
        Vector4 temp(*this);

        this->X = rhs.m11 * temp.X + rhs.m12 * temp.Y + rhs.m13 * temp.Z + rhs.m14 * temp.W;
        this->Y = rhs.m21 * temp.X + rhs.m22 * temp.Y + rhs.m23 * temp.Z + rhs.m24 * temp.W;
        this->Z = rhs.m31 * temp.X + rhs.m32 * temp.Y + rhs.m33 * temp.Z + rhs.m34 * temp.W;
        this->W = rhs.m41 * temp.X + rhs.m42 * temp.Y + rhs.m43 * temp.Z + rhs.m44 * temp.W;

        return *this;
    }

    double Vector4::Length() const
    {
        return std::sqrt(this->X * this->X + this->Y * this->Y + this->Z * this->Z + this->W * this->W);
    }

    Vector4& Vector4::Normalize()
    {
        return *this /= this->Length();
    }

} // namespace Math
