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
        : size(size), data(new char[size])
        {
            
        }
    }
}
