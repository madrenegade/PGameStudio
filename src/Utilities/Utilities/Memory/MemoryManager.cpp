/* 
 * File:   MemoryManager.cpp
 * Author: madrenegade
 * 
 * Created on August 31, 2011, 3:34 PM
 */

#include <stdlib.h>
#include <stdexcept>

#include "Utilities/Memory/MemoryManager.h"
#include "Utilities/Memory/MemoryManager.h"
#include "Utilities/Memory/OutOfMemoryException.h"
#include "Utilities/Memory/Pool.h"
#include "Utilities/Memory/AllocationException.h"

namespace Utilities
{
    namespace Memory
    {

        MemoryManager::MemoryManager(const MemoryManagerSettings& settings)
        : AbstractMemoryManager(settings.maxMemoryForSmallObjects + settings.maxMemoryForLargeObjects), settings(settings),
        smallObjects(settings.maxMemoryForSmallObjects, settings.smallObjectDefaultPageSize),
        largeObjects(settings.maxMemoryForLargeObjects, settings.largeObjectDefaultPageSize),
        newestPool(0)
        {

        }

        pool_id MemoryManager::createPoolForSmallObjects(size_t size)
        {
            pool_id id = newestPool;
            smallObjects.createPool(size, id);
            ++newestPool;
            
            return id;
        }

        pool_id MemoryManager::createPoolForLargeObjects(size_t size)
        {
            pool_id id = newestPool;
            largeObjects.createPool(size, id);
            ++newestPool;
            
            return id;
        }

        pointer MemoryManager::allocate(size_t bytes, pool_id poolId, char prealloc)
        {
            AbstractMemoryManager* manager = getManagerFor(bytes);

            if (manager->getFreeMemory() < bytes)
            {
                throw OutOfMemoryException();
            }
            
            Pool* pool = manager->getPoolManager()->get(poolId);
            
            pointer ptr = pool->allocate(bytes);
            
            setMemory(ptr, bytes, prealloc);
            
            return ptr;
        }

        void MemoryManager::deallocate(const_pointer ptr, size_t sizeOfOne, size_t n, pool_id poolId)
        {
            const size_t BYTES_TO_DEALLOCATE = n * sizeOfOne;
            
            AbstractMemoryManager* manager = getManagerFor(BYTES_TO_DEALLOCATE);
            
            Pool* pool = manager->getPoolManager()->get(poolId);
            
            if(n == 1)
            {
                pool->deallocate(ptr, BYTES_TO_DEALLOCATE);
            }
            else
            {
                pool->deallocateArray(ptr, BYTES_TO_DEALLOCATE);
            }
        }

        const size_t MemoryManager::getFreeMemory() const
        {
            return smallObjects.getFreeMemory() + largeObjects.getFreeMemory();
        }

        AbstractMemoryManager* MemoryManager::getManagerFor(size_t bytes)
        {
            if (bytes <= settings.threshold)
            {
                return &smallObjects;
            }

            return &largeObjects;
        }

        MemoryTracker* MemoryManager::getTrackerFor(size_t bytes)
        {
            return getManagerFor(bytes)->getTracker();
        }
        
        void MemoryManager::createPool(size_t size, pool_id pool)
        {
            throw std::logic_error("MemoryManager cannot create pools");
        }
    }
}

