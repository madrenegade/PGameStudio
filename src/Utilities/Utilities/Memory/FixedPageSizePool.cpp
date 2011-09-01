/* 
 * File:   FixedPageSizePool.cpp
 * Author: madrenegade
 * 
 * Created on September 1, 2011, 4:29 PM
 */

#include <stdexcept>

#include "Utilities/Memory/FixedPageSizePool.h"

namespace Utilities
{
    namespace Memory
    {

        FixedPageSizePool::FixedPageSizePool(size_t totalSize, size_t pageSize)
        : Pool(totalSize), pageSize(pageSize)
        {
            assertPageSize();
        }

        pointer FixedPageSizePool::allocate(size_t bytes)
        {
            
        }

        void FixedPageSizePool::deallocate(const_pointer ptr, size_t bytes)
        {
            
        }
        
        void FixedPageSizePool::deallocateArray(const_pointer ptr, size_t bytes)
        {
            
        }
        
        void FixedPageSizePool::assertPageSize() const
        {
            assertPageSizeIsNotZero();
            assertPageSizeIsMultipleOfPoolSize();
        }
        
        void FixedPageSizePool::assertPageSizeIsNotZero() const
        {
            if(pageSize == 0)
            {
                throw std::invalid_argument("Page size must not be zero");
            }
        }
        
        void FixedPageSizePool::assertPageSizeIsMultipleOfPoolSize() const
        {
            if(size % pageSize != 0)
            {
                throw std::invalid_argument("Page size must be a multiple of the pool size");
            }
        }
    }
}

