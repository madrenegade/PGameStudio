/* 
 * File:   Pool.cpp
 * Author: madrenegade
 * 
 * Created on September 1, 2011, 4:27 PM
 */

#include "Utilities/Memory/Pool.h"
#include "MemoryPoolSettings.h"
#include "MediumObjectAllocator.h"

namespace Utilities
{
    namespace Memory
    {

        Pool::Pool(const MemoryPoolSettings& settings)
        : settings(settings), 
            smallObjects(settings.smallObjectPoolSize, settings.smallObjectPageSize, settings.smallObjectBlockSize),
            mediumObjects(settings.mediumObjectPoolSize, settings.mediumObjectPageSize, settings.mediumObjectBlockSize),
            largeObjects(settings.largeObjectPoolSize, settings.largeObjectPageSize, settings.largeObjectBlockSize)
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
