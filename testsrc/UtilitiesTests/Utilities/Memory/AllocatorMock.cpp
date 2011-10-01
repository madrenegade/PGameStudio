/*
 * File:   AllocatorMock.cpp
 * Author: madrenegade
 *
 * Created on September 5, 2011, 2:40 PM
 */

#include "Utilities/Memory/AllocatorMock.h"
#include "Utilities/Memory/Pages/PageManager.h"

namespace Utilities
{
    namespace Memory
    {
        AllocatorMock::AllocatorMock(const size_t maxSize, const size_t pageSize, const size_t blockSize)
            : Allocator(PageManager::create(maxSize, pageSize), blockSize)
        {

        }

        byte_pointer AllocatorMock::allocate(const size_t /*bytes*/)
        {
            return pageManager->requestNewPage();
        }

        void AllocatorMock::deallocate(const_byte_pointer /*ptr*/, const size_t /*sizeOfOneObject*/, const size_t /*numObjects*/)
        {

        }

        size_t AllocatorMock::getFreeMemory() const
        {
            return 0;
        }

        size_t AllocatorMock::getLargestFreeArea() const
        {
            return 0;
        }
    }
}
