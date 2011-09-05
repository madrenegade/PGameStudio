/* 
 * File:   AllocatorMock.cpp
 * Author: madrenegade
 * 
 * Created on September 5, 2011, 2:40 PM
 */

#include "Utilities/Memory/AllocatorMock.h"

namespace Utilities
{
    namespace Memory
    {
        AllocatorMock::AllocatorMock(size_t maxSize, size_t pageSize, size_t blockSize)
        : Allocator(maxSize, pageSize, blockSize)
        {
            
        }

        pointer AllocatorMock::allocate(size_t bytes)
        {
            return requestNewPage();
        }

        void AllocatorMock::deallocate(const_pointer ptr, size_t sizeOfOneObject, size_t numObjects)
        {

        }

        size_t AllocatorMock::getFreeMemory() const
        {

        }

        size_t AllocatorMock::getLargestFreeArea() const
        {

        }
    }
}
