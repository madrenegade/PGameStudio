/* 
 * File:   MemoryManager.h
 * Author: madrenegade
 *
 * Created on August 31, 2011, 3:34 PM
 */

#ifndef UTILITIES_MEMORY_MEMORYMANAGER_H
#define	UTILITIES_MEMORY_MEMORYMANAGER_H

#include <boost/shared_ptr.hpp>
#include <glog/logging.h>
#include <glog/raw_logging.h>
#include <map>

#include "Utilities/Memory/typedefs.h"
#include "Utilities/Memory/Pool.h"
#include "Utilities/Memory/MemoryTracker.h"

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
             * @param obj - the object to place in the pool
             * @param poolID - the pool to place the object in
             * @return a pointer to the object
             */
            template<typename T>
            T* construct(const T& obj, pool_id poolID = 0)
            {
                return new (allocate<T > (1, poolID)) T(obj);
            }

            /**
             * destruct the given object, the pool is automatically detected
             * @param ptr - a pointer to the object to destroy
             */
            template<typename T>
            void destruct(const T* ptr)
            {
                deallocate<T > (ptr, 1);
            }

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

                RAW_VLOG(1, "Allocating %i bytes in pool %i", BYTES_TO_ALLOCATE, poolID);

#ifdef DEBUG
                assertPoolExists(poolID);
                
                pointer rawPtr = pools[poolID]->allocate(BYTES_TO_ALLOCATE);

                setMemory(rawPtr, BYTES_TO_ALLOCATE, 'a');

                T* ptr = reinterpret_cast<T*> (rawPtr);
#else
                T* ptr = reinterpret_cast<T*> (pools[poolID]->allocate(BYTES_TO_ALLOCATE));
#endif

                RAW_VLOG(1, "Allocated %i bytes in pool %i", BYTES_TO_ALLOCATE, poolID);

                memoryTracker->trackAllocation(ptr, BYTES_TO_ALLOCATE);

                return ptr;
            }

            /**
             * deallocate space for a bunch of objects
             * @param ptr - the starting address of the space to deallocate
             * @param n - the amount of objects to determine how much space must be deallocated
             */
            template<typename T>
            void deallocate(const T* ptr, size_t n)
            {
                const size_t BYTES_TO_DEALLOCATE = n * sizeof (T);

                RAW_VLOG(1, "Deallocating %i bytes", BYTES_TO_DEALLOCATE);

                const_pointer rawPtr = reinterpret_cast<const_pointer> (ptr);

                Pool* pool = findPoolContaining(rawPtr);

                pool->deallocate(rawPtr, sizeof (T), n);

                RAW_VLOG(1, "Deallocated %i bytes from pool %i", BYTES_TO_DEALLOCATE, findPoolIdFor(pool));

                memoryTracker->trackDeallocation(ptr, BYTES_TO_DEALLOCATE);
            }

            size_t getFreeMemory() const;
            size_t getFreeMemory(pool_id poolID) const;

        private:
            boost::shared_ptr<MemoryTracker> memoryTracker;

            typedef std::map<pool_id, boost::shared_ptr<Pool> > PoolMap;
            PoolMap pools;
            
            pool_id latestPoolID;

            Pool* findPoolContaining(const_pointer ptr) const;
            pool_id findPoolIdFor(Pool* pool) const;
            
            void assertPoolIsUnique(const boost::shared_ptr<Pool>& pool) const;

#ifdef DEBUG
            void assertPoolExists(pool_id poolID) const;
            static void setMemory(pointer ptr, size_t bytes, char c);
#endif
        };
    }
}

#endif	/* UTILITIES_MEMORY_MEMORYMANAGER_H */

