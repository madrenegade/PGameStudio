/* 
 * File:   MemoryManager.cpp
 * Author: madrenegade
 * 
 * Created on August 31, 2011, 3:34 PM
 */
#include <stdexcept>

#include "Utilities/Memory/MemoryManager.h"

namespace Utilities
{
    namespace Memory
    {

        MemoryManager::MemoryManager(const boost::shared_ptr<MemoryTracker>& memoryTracker)
        : memoryTracker(memoryTracker)
        {
        }

        size_t MemoryManager::getFreeMemory() const
        {
            size_t freeMemory = 0;
            
            for(PoolMap::const_iterator i = pools.begin(); i != pools.end(); ++i)
            {
                freeMemory += i->second->getFreeMemory();
            }
            
            return freeMemory;
        }
        
        size_t MemoryManager::getFreeMemory(pool_id poolID) const
        {
#ifdef DEBUG
            assertPoolExists(poolID);
#endif
            return pools.at(poolID)->getFreeMemory();
        }
        
        Pool* MemoryManager::findPoolContaining(const_pointer ptr) const
        {
            for(PoolMap::const_iterator i = pools.begin(); i != pools.end(); ++i)
            {
                if(i->second->contains(ptr))
                {
                    return i->second.get();
                }
            }
            
            throw std::logic_error("Pointer not found in registered pools");
        }
        
        pool_id MemoryManager::findPoolIdFor(Pool* pool) const
        {
            for(PoolMap::const_iterator i = pools.begin(); i != pools.end(); ++i)
            {
                if(i->second.get() == pool)
                {
                    return i->first;
                }
            }
            
            throw std::logic_error("Pool id not found for given pool");
        }
        
#ifdef DEBUG
        void MemoryManager::assertPoolExists(pool_id poolID) const
        {
            if(pools.find(poolID) == pools.end())
            {
                throw std::logic_error("Invalid pool id");
            }
        }
        
        void MemoryManager::setMemory(pointer ptr, size_t bytes, char c)
        {
            for(size_t i = 0; i < bytes; ++i)
            {
                ptr[i] = c;
            }
        }
#endif
    }
}

