/* 
 * File:   AllocationException.h
 * Author: madrenegade
 *
 * Created on August 31, 2011, 3:01 PM
 */

#ifndef ALLOCATIONEXCEPTION_H
#define	ALLOCATIONEXCEPTION_H

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


#endif	/* ALLOCATIONEXCEPTION_H */

