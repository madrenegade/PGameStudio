/* 
 * File:   LargeObjectAllocator.cpp
 * Author: madrenegade
 * 
 * Created on September 2, 2011, 11:00 PM
 */

#include "Utilities/Memory/Allocators/LargeObjectAllocator.h"
#include <stdexcept>

namespace Utilities
{
    namespace Memory
    {
        LargeObjectAllocator::LargeObjectAllocator(size_t maxSize, size_t pageSize, size_t blockSize)
        : Allocator(maxSize, pageSize, blockSize)
        {
            
        }

        pointer LargeObjectAllocator::allocate(size_t bytes)
        {
            throw std::runtime_error("LargeObjectAllocator not implemented");
            return new byte[bytes];
        }

        void LargeObjectAllocator::deallocate(const_pointer ptr, size_t sizeOfOneObject, size_t numObjects)
        {
            delete[] ptr;
        }

        size_t LargeObjectAllocator::getLargestFreeArea() const
        {

        }

        size_t LargeObjectAllocator::getFreeMemory() const
        {

        }
    }
}

