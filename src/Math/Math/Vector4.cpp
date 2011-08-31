#include "Math/Vector4.h"
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

    double Vector4::Length() const
    {
        return std::sqrt(this->X *this->X + this->Y * this->Y + this->Z * this->Z + this->W * this->W);
    }

    Vector4& Vector4::Normalize()
    {
        return *this /= this->Length();
    }

} // namespace Math
