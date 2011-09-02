/* 
 * File:   PoolMock.cpp
 * Author: madrenegade
 * 
 * Created on September 2, 2011, 12:55 PM
 */

#include "Utilities/Memory/PoolMock.h"

namespace Utilities
{
    namespace Memory
    {
        PoolMock::PoolMock()
        : Pool(100), data(new char[100]), allocations(0), deallocations(0)
        {
        }
        
        pointer PoolMock::allocate(size_t bytes)
        {
            ++allocations;
            return data.get();
        }
        
        void PoolMock::deallocate(const_pointer ptr, size_t sizeOfOneObject, size_t numObjects)
        {
            ++deallocations;
        }

        bool PoolMock::contains(const_pointer ptr) const
        {
            return true;
        }

        size_t PoolMock::getMemoryUsage() const
        {
            return sizeof(int);
        }
        
        unsigned int PoolMock::getAllocations() const
        {
            return allocations;
        }
        
        unsigned int PoolMock::getDeallocations() const
        {
            return deallocations;
        }
    }
}
