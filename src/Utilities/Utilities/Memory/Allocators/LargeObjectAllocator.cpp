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
        LargeObjectAllocator::LargeObjectAllocator(const boost::shared_ptr<PageManager>& pageManager, size_t blockSize)
        : Allocator(pageManager, blockSize)
        {
            
        }

        byte_pointer LargeObjectAllocator::allocate(size_t bytes)
        {
            throw std::runtime_error("LargeObjectAllocator not implemented");
//            return new byte[bytes];
        }

        void LargeObjectAllocator::deallocate(const_byte_pointer ptr, size_t sizeOfOneObject, size_t numObjects)
        {
            delete[] ptr;
        }

        size_t LargeObjectAllocator::getFreeMemory() const
        {

        }
    }
}

