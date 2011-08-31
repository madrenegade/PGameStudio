/* 
 * File:   MemoryManager.cpp
 * Author: madrenegade
 * 
 * Created on August 31, 2011, 3:34 PM
 */

#include <stdlib.h>

#include "Utilities/Memory/MemoryManager.h"
#include "MemoryManager.h"
#include "OutOfMemoryException.h"

namespace Utilities
{
    namespace Memory
    {
        MemoryManager::MemoryManager(size_t threshold, size_t maxMemoryForSmallObjects, size_t maxMemoryForLargeObjects)
        : AbstractMemoryManager(maxMemoryForSmallObjects * maxMemoryForLargeObjects), threshold(threshold),
            smallObjects(maxMemoryForSmallObjects),
            largeObjects(maxMemoryForLargeObjects)
        {
            
        }
        
        AbstractMemoryManager::pointer MemoryManager::allocate(size_t n, unsigned char prealloc)
        {
            if(n <= threshold)
            {
                if(smallObjects.getFreeMemory() < n)
                {
                    throw OutOfMemoryException();
                }
                
                return smallObjects.allocate(n, prealloc);
            }
            else
            {
                if(largeObjects.getFreeMemory() < n)
                {
                    throw OutOfMemoryException();
                }
                
                return largeObjects.allocate(n, prealloc);
            }
        }
        
        void MemoryManager::deallocate(const_pointer ptr, size_t sizeOfOne, size_t n)
        {
            if(n <= threshold)
            {
                smallObjects.deallocate(ptr, sizeOfOne, n);
            }
            else
            {
                largeObjects.deallocate(ptr, sizeOfOne, n);
            }
        }
        
        const size_t MemoryManager::getFreeMemory() const
        {
            return smallObjects.getFreeMemory() + largeObjects.getFreeMemory();
        }
        
        MemoryTracker* MemoryManager::getTrackerFor(size_t bytes)
        {
            if(bytes <= threshold)
            {
                return smallObjects.getTracker();
            }
            else
            {
                return largeObjects.getTracker();
            }
        }
    }
}

