/*
 * File:   DivideByZeroException.cpp
 * Author: madrenegade
 *
 * Created on June 13, 2011, 8:54 AM
 */

#include "DivideByZeroException.h"

namespace Math
{

    DivideByZeroException::DivideByZeroException(const std::string& argument)
        : std::invalid_argument(argument)
    {

    }
}
