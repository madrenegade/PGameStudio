/* 
 * File:   MemoryManager.cpp
 * Author: madrenegade
 * 
 * Created on August 31, 2011, 3:34 PM
 */
#include <stdexcept>

#include "Utilities/Memory/MemoryManager.h"
#include "STLAllocator.h"

namespace Utilities
{
    namespace Memory
    {

        MemoryManager::Ptr MemoryManager::create(const MemoryTracker::Ptr& memoryTracker)
        {
            // check platform details about type sizes
            
            BOOST_STATIC_ASSERT(sizeof(char) == 1);
            BOOST_STATIC_ASSERT(sizeof(short) == 2);
            BOOST_STATIC_ASSERT(sizeof(int) == 4);
            BOOST_STATIC_ASSERT(sizeof(long) == 8);
            BOOST_STATIC_ASSERT(sizeof(float) == 4);
            BOOST_STATIC_ASSERT(sizeof(double) == 8);
            BOOST_STATIC_ASSERT(sizeof(void*) == 8);
            
            Ptr ptr(new MemoryManager(memoryTracker));

            STLAllocator<void>::memory = ptr;

            return ptr;
        }

        MemoryManager::MemoryManager(const boost::shared_ptr<MemoryTracker>& memoryTracker)
        : memoryTracker(memoryTracker), latestPoolID()
#ifdef DEBUG
        , profilerClient(new memprof::client("127.0.0.1"))
#endif
        {
#ifdef DEBUG
            profilerClient->connect();
#endif
        }

        pool_id MemoryManager::registerMemoryPool(const boost::shared_ptr<Pool>& pool)
        {
#ifdef DEBUG
            assertPoolIsUnique(pool);
#endif

            const pool_id id = latestPoolID.fetch_and_add(1);

            {
                PoolMapMutexType::scoped_lock lock(poolMapMutex, true);

                pools[id] = pool;
            }

            return id;
        }

        void MemoryManager::unregisterMemoryPool(const pool_id poolID)
        {
            PoolMapMutexType::scoped_lock lock(poolMapMutex, true);

#ifdef DEBUG
            if (pools.find(poolID) == pools.end())
            {
                throw std::logic_error("Pool not found");
            }
#endif

            pools.erase(poolID);
        }
        
        size_t  MemoryManager::getMemoryUsage() const
        {
            size_t memory = 0;
            
            for (PoolMap::const_iterator i = pools.begin(); i != pools.end(); ++i)
            {
                memory += i->second->getMemoryUsage();
            }
            
            return memory;
        }

        pool_id MemoryManager::findPoolContaining(const_byte_pointer ptr) const
        {
            DCHECK(!pools.empty());

            for (PoolMap::const_iterator i = pools.begin(); i != pools.end(); ++i)
            {
                if (i->second->contains(ptr))
                {
                    return i->first;
                }
            }

            VLOG(1) << "Pointer " << reinterpret_cast<const void*> (ptr) << " not found in any of the registered memory pools";

            VLOG(1) << "Registered pools: " << pools.size();

            for (PoolMap::const_iterator i = pools.begin(); i != pools.end(); ++i)
            {
                VLOG(1) << "[id: " << i->first << ", address: " << reinterpret_cast<const void*> (i->second.get()) << "]";
            }

            memoryTracker->printMemoryDump();

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

