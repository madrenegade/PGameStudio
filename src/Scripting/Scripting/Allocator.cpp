/*
 * File:   Allocator.cpp
 * Author: madrenegade
 *
 * Created on September 28, 2011, 9:06 PM
 */

#include "Scripting/Allocator.h"
#include "Utilities/functions.h"

#include <glog/logging.h>

namespace Scripting
{
    Utilities::Memory::MemoryManager* Allocator::memory;
    Utilities::Memory::pool_id Allocator::pool = 0;

    void* Allocator::allocate(void*, void* ptr, size_t oldSize, size_t newSize)
    {
        Utilities::Memory::byte_pointer newPtr = 0;

        if (newSize > 0)
        {
#ifdef DEBUG
            newPtr = memory->rawAllocate<Utilities::Memory::byte > (newSize, StackTrace(), pool);
#else
            newPtr = memory->rawAllocate<Utilities::Memory::byte > (newSize, pool);
#endif
        }

        if (oldSize != 0 && newSize > 0)
        {
            const size_t bytesToCopy = std::min(oldSize, newSize);

            Utilities::copy(reinterpret_cast<Utilities::Memory::const_byte_pointer> (ptr), newPtr, bytesToCopy);
        }

        if (oldSize != 0)
        {
            memory->rawDeallocate(reinterpret_cast<Utilities::Memory::const_byte_pointer> (ptr), oldSize);
        }

        return newPtr;
    }

    Allocator::Allocator()
    {
    }

    Allocator::~Allocator()
    {
    }
}


