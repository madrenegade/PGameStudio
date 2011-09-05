/* 
 * File:   MemoryManager.h
 * Author: madrenegade
 *
 * Created on August 31, 2011, 3:34 PM
 */

#ifndef UTILITIES_MEMORY_MEMORYMANAGER_H
#define	UTILITIES_MEMORY_MEMORYMANAGER_H

#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/static_assert.hpp>

#include <glog/logging.h>
#include <glog/raw_logging.h>
#include <map>
#include <stdexcept>

#include "Utilities/Memory/typedefs.h"
#include "Utilities/Memory/Pool.h"
#include "Utilities/Memory/Tracking/MemoryTracker.h"
#include "Utilities/functions.h"

namespace Utilities
{
    namespace Memory
    {

        class MemoryManager
        {
        public:
            MemoryManager(const boost::shared_ptr<MemoryTracker>& memoryTracker);

            /**
             * registers a new memory pool and returns an id to access it
             * the first registration always returns 0 as the id
             * 
             * @param pool - the pool to register
             * @return the id the pool is registered to
             */
            pool_id registerMemoryPool(const boost::shared_ptr<Pool>& pool);

            /**
             * construct the given object in the given memory pool
             * make sure that the memory manager instance exists when the ptr gets deleted
             * 
             * @param obj - the object to place in the pool
             * @param poolID - the pool to place the object in
             * @return a pointer to the object
             */
            template<typename T>
            boost::shared_ptr<T> construct(const T& obj, pool_id poolID = 0)
            {
                boost::shared_ptr<T> ptr(new (allocate<T > (1, poolID)) T(obj),
                                         boost::bind(&MemoryManager::deallocate<T, 1 >, this, _1));
                return ptr;
            }

            template<typename T, size_t numObjects>
            boost::shared_array<T> allocate(pool_id poolID = 0)
            {
#ifdef DEBUG
                BOOST_STATIC_ASSERT(numObjects > 1);
#endif

                boost::shared_array<T> ptr(allocate<T > (numObjects, poolID),
                                           boost::bind(&MemoryManager::deallocate<T, numObjects>, this, _1));
                return ptr;
            }

        private:
            boost::shared_ptr<MemoryTracker> memoryTracker;

            typedef std::map<pool_id, boost::shared_ptr<Pool> > PoolMap;
            PoolMap pools;

            pool_id latestPoolID;

            Pool* findPoolContaining(const_pointer ptr) const;
            pool_id findPoolIdFor(Pool* pool) const;

            void assertPoolIsUnique(const boost::shared_ptr<Pool>& pool) const;

            /**
             * allocate space for a bunch of objects
             * @param numObjects - the amount of objects to allocate space for
             * @param poolID - the pool in which the space should be allocated
             * @return a pointer to the beginning of the allocated space
             */
            template<typename T>
            T* allocate(size_t numObjects, pool_id poolID = 0)
            {
                const size_t BYTES_TO_ALLOCATE = numObjects * sizeof (T);

#ifdef DEBUG
                RAW_VLOG(1, "Allocating %i bytes in pool %i", BYTES_TO_ALLOCATE, poolID);
#endif

#ifdef DEBUG
                assertPoolExists(poolID);

                pointer rawPtr = pools[poolID]->allocate(BYTES_TO_ALLOCATE);

                fillMemory(rawPtr, BYTES_TO_ALLOCATE, ALLOCATED);

                T* ptr = reinterpret_cast<T*> (rawPtr);
#else
                T* ptr = reinterpret_cast<T*> (pools[poolID]->allocate(BYTES_TO_ALLOCATE));
#endif

#ifdef DEBUG
                RAW_VLOG(1, "Allocated %i bytes in pool %i", BYTES_TO_ALLOCATE, poolID);
#endif

                memoryTracker->trackAllocation(ptr, BYTES_TO_ALLOCATE);

                return ptr;
            }

            /**
             * deallocate space for a bunch of objects
             * @param ptr - the starting address of the space to deallocate
             * @param n - the amount of objects to determine how much space must be deallocated
             */
            template<typename T, size_t n>
            void deallocate(const T* ptr)
            {
                const size_t BYTES_TO_DEALLOCATE = n * sizeof (T);

#ifdef DEBUG
                RAW_VLOG(1, "Deallocating %i bytes", BYTES_TO_DEALLOCATE);
#endif

                const_pointer rawPtr = reinterpret_cast<const_pointer> (ptr);

                Pool* pool = findPoolContaining(rawPtr);

                pool->deallocate(rawPtr, sizeof (T), n);

#ifdef DEBUG
                RAW_VLOG(1, "Deallocated %i bytes from pool %i", BYTES_TO_DEALLOCATE, findPoolIdFor(pool));
#endif

                memoryTracker->trackDeallocation(ptr, BYTES_TO_DEALLOCATE);
            }

#ifdef DEBUG
            void assertPoolExists(pool_id poolID) const;
#endif
        };
    }
}

#endif	/* UTILITIES_MEMORY_MEMORYMANAGER_H */

