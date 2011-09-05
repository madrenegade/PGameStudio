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
        : memoryTracker(memoryTracker), latestPoolID()
        {
        }

        pool_id MemoryManager::registerMemoryPool(const boost::shared_ptr<Pool>& pool)
        {
#ifdef DEBUG
            assertPoolIsUnique(pool);
#endif

            pool_id id = latestPoolID.fetch_and_add(1);

            pools.insert(std::make_pair(id, pool));

            return id;
        }

        pool_id MemoryManager::findPoolContaining(const_pointer ptr) const
        {
            // TODO: is iterating thread safe?
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

        void MemoryManager::assertPoolExists(pool_id poolID) const
        {  
            if (pools.count(poolID) == 0)
            {
                throw std::logic_error("Invalid pool id");
            }
        }

        void MemoryManager::assertPoolIsUnique(const boost::shared_ptr<Pool>& pool) const
        {
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

