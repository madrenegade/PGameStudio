#include "Math/Vector4.h"
#include "Matrix4.h"
#include <cmath>

namespace Math
{

    Vector4::Vector4(double x, double y, double z, double w)
        : X(x), Y(y), Z(z), W(w)
    {
        //ctor
    }

    Vector4::~Vector4()
    {
        //dtor
    }

    Vector4& Vector4::operator /= (double value)
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
        
        this->X = rhs.M11() * temp.X + rhs.M12() * temp.Y + rhs.M13() * temp.Z + rhs.M14() * temp.W;
        this->Y = rhs.M21() * temp.X + rhs.M22() * temp.Y + rhs.M23() * temp.Z + rhs.M24() * temp.W;
        this->Z = rhs.M31() * temp.X + rhs.M32() * temp.Y + rhs.M33() * temp.Z + rhs.M34() * temp.W;
        this->W = rhs.M41() * temp.X + rhs.M42() * temp.Y + rhs.M43() * temp.Z + rhs.M44() * temp.W;
        
        return *this;
    }

    double Vector4::Length() const
    {
        return std::sqrt(this->X *this->X + this->Y * this->Y + this->Z * this->Z + this->W * this->W);
    }

    Vector4& Vector4::Normalize()
    {
        return *this /= this->Length();
    }

} // namespace Math
