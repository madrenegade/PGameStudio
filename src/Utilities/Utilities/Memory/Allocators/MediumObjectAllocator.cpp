/* 
 * File:   MediumObjectAllocator.cpp
 * Author: madrenegade
 * 
 * Created on September 2, 2011, 10:59 PM
 */

#include "Utilities/Memory/Allocators/MediumObjectAllocator.h"

namespace Utilities
{
    namespace Memory
    {
        MediumObjectAllocator::MediumObjectAllocator(size_t maxSize, size_t pageSize, size_t blockSize)
        : Allocator(maxSize, pageSize, blockSize)
        {
            
        }

        pointer MediumObjectAllocator::allocate(size_t bytes)
        {
            return new byte[bytes];
        }

        void MediumObjectAllocator::deallocate(const_pointer ptr, size_t sizeOfOneObject, size_t numObjects)
        {
            delete[] ptr;
        }

        size_t MediumObjectAllocator::getLargestFreeArea() const
        {

        }

        size_t MediumObjectAllocator::getFreeMemory() const
        {

        }
    }
}