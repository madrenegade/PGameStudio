/* 
 * File:   STLAllocator.cpp
 * Author: madrenegade
 * 
 * Created on September 8, 2011, 12:04 PM
 */

#include "Utilities/Memory/STLAllocator.h"

namespace Utilities
{
    namespace Memory
    {
        MemoryManager::Ptr STLAllocator<void>::memory;
    }
}
