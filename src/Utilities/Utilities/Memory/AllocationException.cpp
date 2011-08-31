/* 
 * File:   AllocationException.cpp
 * Author: madrenegade
 * 
 * Created on August 31, 2011, 3:01 PM
 */

#include "Utilities/Memory/AllocationException.h"

namespace Utilities
{
    namespace Memory
    {
        AllocationException::AllocationException()
        : std::logic_error("Allocation error")
        {

        }
    }
}


