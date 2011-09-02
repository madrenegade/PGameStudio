/* 
 * File:   SmallObjectAllocator.cpp
 * Author: madrenegade
 * 
 * Created on September 2, 2011, 10:55 PM
 */

#include "Utilities/Memory/SmallObjectAllocator.h"

namespace Utilities
{
    namespace Memory
    {
        SmallObjectAllocator::SmallObjectAllocator(size_t maxSize, size_t pageSize, size_t blockSize)
        : Allocator(maxSize, pageSize, blockSize)
        {
            
        }
        
        pointer SmallObjectAllocator::allocate(size_t bytes)
        {
            // get page with enough space or throw OutOfMemory
            
        }
        
        void SmallObjectAllocator::deallocate(const_pointer ptr, size_t sizeOfOneObject, size_t numObjects)
        {
            
        }

        size_t SmallObjectAllocator::getLargestFreeArea() const
        {
            
        }
        
        size_t SmallObjectAllocator::getFreeMemory() const
        {
            
        }
    }
}


