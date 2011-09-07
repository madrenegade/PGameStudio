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
        MemoryManager::Ptr MemoryManager::create(const MemoryTracker::Ptr& memoryTracker)
        {
            return Ptr(new MemoryManager(memoryTracker));
        }

        MemoryManager::MemoryManager(const boost::shared_ptr<MemoryTracker>& memoryTracker)
        : memoryTracker(memoryTracker), latestPoolID(), profilerClient(new memprof::client("127.0.0.1"))
        {
            profilerClient->connect();
        }

        pool_id MemoryManager::registerMemoryPool(const boost::shared_ptr<Pool>& pool)
        {
#ifdef DEBUG
            assertPoolIsUnique(pool);
#endif

            pool_id id = latestPoolID.fetch_and_add(1);

            {
                PoolMapMutexType::scoped_lock lock(poolMapMutex, true);
                
                pools[id] = pool;
            }
            
            return id;
        }
        
        void MemoryManager::unregisterMemoryPool(pool_id poolID)
        {
            PoolMapMutexType::scoped_lock lock(poolMapMutex, true);
            
#ifdef DEBUG
            if(pools.find(poolID) == pools.end())
            {
                throw std::logic_error("Pool not found");
            }
#endif
            
            pools.erase(poolID);
        }

        pool_id MemoryManager::findPoolContaining(const_pointer ptr) const
        {
            for (PoolMap::const_iterator i = pools.begin(); i != pools.end(); ++i)
            {
                if (i->second->contains(ptr))
                {
                    return i->first;
                }
            }

            throw std::logic_error("Pointer not found in registered pools");
        }

#ifdef DEBUG

        void MemoryManager::assertPoolIsUnique(const boost::shared_ptr<Pool>& pool)
        {
            PoolMapMutexType::scoped_lock lock(poolMapMutex, false);
            
            for (PoolMap::const_iterator i = pools.begin(); i != pools.end(); ++i)
            {
                if (i->second == pool)
                {
                    throw std::logic_error("This pool is already registered");
                }
            }
        }
#endif
    }
}

