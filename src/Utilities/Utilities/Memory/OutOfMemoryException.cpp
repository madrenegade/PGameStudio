/* 
 * File:   OutOfMemoryException.cpp
 * Author: madrenegade
 * 
 * Created on August 31, 2011, 5:06 PM
 */
#include "Utilities/Memory/OutOfMemoryException.h"

namespace Utilities
{
    namespace Memory
    {
        OutOfMemoryException::OutOfMemoryException(const std::string& cause)
        : std::runtime_error(cause)
        {
            
        }
    }
}
