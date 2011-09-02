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
        : memoryTracker(memoryTracker), latestPoolID(0)
        {
        }
        
        pool_id MemoryManager::registerMemoryPool(const boost::shared_ptr<Pool>& pool)
        {
            assertPoolIsUnique(pool);
            
            pool_id id = latestPoolID;
            
            pools[id] = pool;
            ++latestPoolID;
            
            return id;
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
        
        void MemoryManager::assertPoolIsUnique(const boost::shared_ptr<Pool>& pool) const
        {
            for(PoolMap::const_iterator i = pools.begin(); i != pools.end(); ++i)
            {
                if(i->second == pool)
                {
                    throw std::logic_error("This pool is already registered");
                }
            }
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

