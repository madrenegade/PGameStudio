#include "Math/Vector3.h"
#include "Math/DivideByZeroException.h"
#include <cmath>

namespace Math {

    Vector3::Vector3(double x, double y, double z)
        : X(x), Y(y), Z(z)
    {
    }

    Vector3::Vector3(const Vector3& v)
        : X(v.X), Y(v.Y), Z(v.Z)
    {
    }

    Vector3::~Vector3()
    {
    }

    Vector3& Vector3::operator/=(double value)
    {
        if(value == 0) {
            throw DivideByZeroException("value");
        }
        
        this->X /= value;
        this->Y /= value;
        this->Z /= value;

        return *this;
    }

    Vector3& Vector3::operator+=(const Vector3& rhs)
    {
        this->X += rhs.X;
        this->Y += rhs.Y;
        this->Z += rhs.Z;

        return *this;
    }

    Vector3& Vector3::operator-=(const Vector3& rhs)
    {
        this->X -= rhs.X;
        this->Y -= rhs.Y;
        this->Z -= rhs.Z;

        return *this;
    }

    Vector3 Vector3::operator+(const Vector3& rhs) const
    {
        return Vector3(this->X + rhs.X, this->Y + rhs.Y, this->Z + rhs.Z);
    }

    Vector3 Vector3::operator-(const Vector3& rhs) const
    {
        return Vector3(this->X - rhs.X, this->Y - rhs.Y, this->Z - rhs.Z);
    }

    Vector3 Vector3::operator-() const
    {
        return Vector3(-this->X, -this->Y, -this->Z);
    }

    Vector3 Vector3::operator*(double value) const
    {
        return Vector3(this->X * value, this->Y * value, this->Z * value);
    }

    Vector3 operator*(double value, const Vector3& v)
    {
        return Vector3(v.X * value, v.Y * value, v.Z * value);
    }

    Vector3& Vector3::Normalize()
    {
        return (*this /= this->Length());
    }

    Vector3 Vector3::Cross(const Vector3& rhs) const
    {
        return Vector3(this->Y * rhs.Z - this->Z * rhs.Y,
                       this->Z * rhs.X - this->X * rhs.Z,
                       this->X * rhs.Y - this->Y * rhs.X);
    }

    double Vector3::Dot(const Vector3& rhs) const
    {
        return this->X * rhs.X + this->Y * rhs.Y + this->Z * rhs.Z;
    }

    double Vector3::Length() const
    {
        return std::sqrt(this->X * this->X + this->Y * this->Y + this->Z * this->Z);
    }

    double Vector3::LengthSquared() const
    {
        return this->X * this->X + this->Y * this->Y + this->Z * this->Z;
    }
} // namespace Math
