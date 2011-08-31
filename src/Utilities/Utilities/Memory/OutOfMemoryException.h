/* 
 * File:   OutOfMemoryException.h
 * Author: madrenegade
 *
 * Created on August 31, 2011, 5:06 PM
 */

#ifndef UTILITIES_MEMORY_OUTOFMEMORYEXCEPTION_H
#define	UTILITIES_MEMORY_OUTOFMEMORYEXCEPTION_H

#include <stdexcept>

namespace Utilities
{
    namespace Memory
    {

        class OutOfMemoryException : public std::runtime_error
        {
        public:
            OutOfMemoryException();
        };
    }
}


#endif	/* UTILITIES_MEMORY_OUTOFMEMORYEXCEPTION_H */

