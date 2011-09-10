/* 
 * File:   Pool.cpp
 * Author: madrenegade
 * 
 * Created on September 1, 2011, 4:27 PM
 */

#include "Utilities/Memory/Pool.h"
#include "Utilities/Memory/MemoryPoolSettings.h"
#include "Utilities/Memory/Allocators/MediumObjectAllocator.h"
#include "Utilities/Memory/Pages/PageManager.h"

namespace Utilities
{
    namespace Memory
    {
        Pool::Ptr Pool::create(const MemoryPoolSettings& settings)
        {
            return Ptr(new Pool(settings));
        }

        Pool::Pool(const MemoryPoolSettings& settings)
        : settings(settings), 
            smallObjects(PageManager::create(settings.smallObjectPoolSize, settings.smallObjectPageSize), settings.smallObjectBlockSize),
            mediumObjects(PageManager::create(settings.mediumObjectPoolSize, settings.mediumObjectPageSize), settings.mediumObjectBlockSize),
            largeObjects(PageManager::create(settings.largeObjectPoolSize, settings.largeObjectPageSize), settings.largeObjectBlockSize)
        {

        }

        pointer Pool::allocate(size_t bytes)
        {
            Allocator* allocator = getAllocatorFor(bytes);
            return allocator->allocate(bytes);
        }
        
        void Pool::deallocate(const_pointer ptr, size_t sizeOfOneObject, size_t numObjects)
        {
            Allocator* allocator = getAllocatorFor(sizeOfOneObject * numObjects);
            allocator->deallocate(ptr, sizeOfOneObject, numObjects);
        }
        
        size_t Pool::getMemoryUsage() const
        {
            return smallObjects.getMemoryUsage() +
                mediumObjects.getMemoryUsage() +
                largeObjects.getMemoryUsage();
        }
        
        bool Pool::contains(const_pointer ptr) const
        {
            return smallObjects.contains(ptr) || mediumObjects.contains(ptr) || largeObjects.contains(ptr);
        }

        Allocator* Pool::getAllocatorFor(size_t bytes)
        {
            if (bytes <= settings.smallObjectBlockSize)
            {
                return &smallObjects;
            }
            else if (bytes >= settings.largeObjectBlockSize)
            {
                return &largeObjects;
            }
            
            return &mediumObjects;
        }
    }
}
