/* 
 * File:   OutOfMemoryException.cpp
 * Author: madrenegade
 * 
 * Created on August 31, 2011, 5:06 PM
 */

#include <stdexcept>

#include "Utilities/Memory/OutOfMemoryException.h"
#include "OutOfMemoryException.h"

namespace Utilities
{
    namespace Memory
    {
        OutOfMemoryException::OutOfMemoryException()
        : std::runtime_error("Out of memory")
        {
            
        }
    }
}
