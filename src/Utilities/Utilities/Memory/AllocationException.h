/* 
 * File:   AllocationException.h
 * Author: madrenegade
 *
 * Created on August 31, 2011, 3:01 PM
 */

#ifndef UTILITIES_MEMORY_ALLOCATIONEXCEPTION_H
#define	UTILITIES_MEMORY_ALLOCATIONEXCEPTION_H

#include <stdexcept>

namespace Utilities
{
    namespace Memory
    {

        class AllocationException : public std::logic_error
        {
        public:
            AllocationException();
        };
    }
}


#endif	/* UTILITIES_MEMORY_ALLOCATIONEXCEPTION_H */

