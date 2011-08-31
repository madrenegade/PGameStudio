#ifndef DIVIDEBYZEROEXCEPTION_H
#define	DIVIDEBYZEROEXCEPTION_H

#include <stdexcept>

namespace Math
{

    class DivideByZeroException : public std::invalid_argument
    {
    public:
        explicit DivideByZeroException(const std::string& argument);
    };
}

#endif	/* DIVIDEBYZEROEXCEPTION_H */

