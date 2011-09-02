/* 
 * File:   Pool.cpp
 * Author: madrenegade
 * 
 * Created on September 1, 2011, 4:27 PM
 */

#include "Utilities/Memory/Pool.h"

namespace Utilities
{
    namespace Memory
    {
        Pool::Pool(size_t size)
        : size(size)
        {
            
        }
        
        size_t Pool::getFreeMemory() const
        {
            return size - getMemoryUsage();
        }
    }
}
