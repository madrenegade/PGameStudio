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
        
        pointer MemoryManager::allocate(size_t bytes, pool_id pool, char prealloc)
        {
            AbstractMemoryManager* manager = getManagerFor(bytes);
            
            if(manager->getFreeMemory() < bytes)
            {
                throw OutOfMemoryException();
            }
                
            return manager->allocate(bytes, pool, prealloc);
        }
        
        void MemoryManager::deallocate(const_pointer ptr, size_t sizeOfOne, size_t n, pool_id pool)
        {
            const size_t BYTES_TO_DEALLOCATE = n * sizeOfOne;
            
            getManagerFor(BYTES_TO_DEALLOCATE)->deallocate(ptr, sizeOfOne, n, pool);
        }
        
        const size_t MemoryManager::getFreeMemory() const
        {
            return smallObjects.getFreeMemory() + largeObjects.getFreeMemory();
        }
        
        AbstractMemoryManager* MemoryManager::getManagerFor(size_t bytes)
        {
            if(bytes <= threshold)
            {
                return &smallObjects;
            }
            
            return &largeObjects;
        }
        
        MemoryTracker* MemoryManager::getTrackerFor(size_t bytes)
        {
            return getManagerFor(bytes)->getTracker();
        }
    }
}

