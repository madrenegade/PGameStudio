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

#include <tbb/concurrent_hash_map.h>
#include <tbb/atomic.h>
#include <tbb/spin_mutex.h>
#include <tbb/spin_rw_mutex.h>

#ifdef DEBUG
#include "../MemoryProfiler/memprof/memprof/client.h"
#include <boost/scoped_ptr.hpp>
#include "StackTrace.h"
#endif

namespace Utilities
{
    namespace Memory
    {

        class MemoryManager
        {
        public:
            typedef boost::shared_ptr<MemoryManager> Ptr;

            /**
             * Create a memory manager instance. This instance is automatically set to be used by the STLAllocator.
             * @param memoryTracker - the memory tracker to use
             * @return the new memory manager instance
             */
            static Ptr create(const MemoryTracker::Ptr& memoryTracker);

            /**
             * registers a new memory pool and returns an id to access it
             * the first registration always returns 0 as the id
             * 
             * @param pool - the pool to register
             * @return the id the pool is registered to
             */
            pool_id registerMemoryPool(const boost::shared_ptr<Pool>& pool);

            /**
             * unregisters the memory pool
             * if the memory manager holds the last reference the pool will be deleted
             * @param poolID
             */
            void unregisterMemoryPool(pool_id poolID);

            /**
             * construct the given object in the given memory pool
             * make sure that the memory manager instance exists when the ptr gets deleted
             * 
             * @param obj - the object to place in the pool
             * @param poolID - the pool to place the object in
             * @return a pointer to the object
             */
            template<typename T>
            boost::shared_ptr<T> construct(const T& obj, pool_id poolID = 0
#ifdef DEBUG
                , const StackTrace& stacktrace = StackTrace()
#endif
                )
            {
#ifdef DEBUG
                {
                    ProfilerClientMutexType::scoped_lock lock(profilerClientMutex);
                    profilerClient->send_allocation_info(stacktrace, sizeof (T), poolID);
                }
#endif

                boost::shared_ptr<T> ptr(new (internalAllocate<T > (1, poolID)) T(obj),
                                         boost::bind(&MemoryManager::deallocate<T>, this, _1, 1));
                return ptr;
            }

            template<typename T, size_t numObjects>
            boost::shared_array<T> allocate(pool_id poolID = 0
#ifdef DEBUG
                , const StackTrace& stacktrace = StackTrace()
#endif
                )
            {
#ifdef DEBUG
                BOOST_STATIC_ASSERT(numObjects > 1);

                {
                    ProfilerClientMutexType::scoped_lock lock(profilerClientMutex);
                    profilerClient->send_allocation_info(stacktrace, numObjects * sizeof (T), poolID);
                }
#endif

                boost::shared_array<T> ptr(internalAllocate<T > (numObjects, poolID),
                                           boost::bind(&MemoryManager::deallocate<T>, this, _1, numObjects));
                return ptr;
            }
            
            template<typename T>
            boost::shared_array<T> allocate(size_t numObjects, pool_id poolID = 0
#ifdef DEBUG
                , const StackTrace& stacktrace = StackTrace()
#endif
                )
            {
#ifdef DEBUG
                assert(numObjects > 1);
                
                {
                    ProfilerClientMutexType::scoped_lock lock(profilerClientMutex);
                    profilerClient->send_allocation_info(stacktrace, numObjects * sizeof (T), poolID);
                }
#endif
                
                boost::shared_array<T> ptr(internalAllocate<T > (numObjects, poolID),
                                           boost::bind(&MemoryManager::deallocate<T>, this, _1, numObjects));
                return ptr;
            }

#ifdef DEBUG

            /**
             * do not use directly
             */
            void beginNewFrame()
            {
                ProfilerClientMutexType::scoped_lock lock(profilerClientMutex);
                profilerClient->begin_new_frame();
            }
#endif

        private:
            MemoryManager(const boost::shared_ptr<MemoryTracker>& memoryTracker);

            typedef tbb::spin_mutex MemoryTrackerMutexType;
            MemoryTrackerMutexType memoryTrackerMutex;
            boost::shared_ptr<MemoryTracker> memoryTracker;

            typedef tbb::spin_rw_mutex PoolMapMutexType;
            typedef std::map<pool_id, boost::shared_ptr<Pool > > PoolMap;

            PoolMapMutexType poolMapMutex;
            PoolMap pools;

            tbb::atomic<pool_id> latestPoolID;

#ifdef DEBUG

            typedef tbb::spin_mutex ProfilerClientMutexType;
            ProfilerClientMutexType profilerClientMutex;
            boost::scoped_ptr<memprof::client> profilerClient;
#endif

            pool_id findPoolContaining(const_byte_pointer ptr) const;
            
            template<typename> friend class STLAllocator;
             /**
             * only for the stl allocator
             * @param numObjects
             * @param poolID
             * @param stacktrace
             * @return 
             */
            template<typename T>
            T* stl_allocate(size_t numObjects
#ifdef DEBUG
                , const StackTrace& stacktrace
#endif
                , pool_id poolID = 0)
            {
#ifdef DEBUG
                {
                    ProfilerClientMutexType::scoped_lock lock(profilerClientMutex);
                    profilerClient->send_allocation_info(stacktrace, numObjects * sizeof (T), poolID);
                }
#endif

                return internalAllocate<T>(numObjects, poolID);
            }

            /**
             * allocate space for a bunch of objects
             * @param numObjects - the amount of objects to allocate space for
             * @param poolID - the pool in which the space should be allocated
             * @return a pointer to the beginning of the allocated space
             */
            template<typename T>
            T* internalAllocate(size_t numObjects, pool_id poolID = 0)
            {
                const size_t BYTES_TO_ALLOCATE = numObjects * sizeof (T);

#ifdef DEBUG
                RAW_VLOG(4, "Allocating %i bytes for %i objects of type %s in pool %i", 
                         BYTES_TO_ALLOCATE, numObjects, 
                         Utilities::demangle(typeid(T).name()).c_str(), poolID);
#endif

                T* ptr = 0;
                {
                    PoolMapMutexType::scoped_lock lock(poolMapMutex, true);

#ifdef DEBUG
                    if (pools.find(poolID) == pools.end())
                    {
                        throw std::logic_error("Invalid pool id");
                    }

                    byte_pointer rawPtr = pools[poolID]->allocate(BYTES_TO_ALLOCATE);

                    fillMemory(rawPtr, BYTES_TO_ALLOCATE, ALLOCATED);

                    ptr = reinterpret_cast<T*> (rawPtr);
                    
                    RAW_VLOG(4, "Allocated %i bytes at address 0x%lx in pool %i (0x%lx)", BYTES_TO_ALLOCATE, ptr, poolID, pools[poolID].get());
#else
                    ptr = reinterpret_cast<T*> (pools[poolID]->allocate(BYTES_TO_ALLOCATE));
#endif
                }

                {
                    MemoryTrackerMutexType::scoped_lock lock(memoryTrackerMutex);
                    memoryTracker->trackAllocation(ptr, BYTES_TO_ALLOCATE);
                }

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

#ifdef DEBUG
                RAW_VLOG(4, "Deallocating %i bytes (address: 0x%lx)", BYTES_TO_DEALLOCATE, ptr);
#endif

                // call destructors
                for (size_t i = 0; i < n; ++i)
                {
                    ptr[i].~T();
                }

                const_byte_pointer rawPtr = reinterpret_cast<const_byte_pointer> (ptr);

                {
                    PoolMapMutexType::scoped_lock lock(poolMapMutex, true);
                    pool_id poolID = findPoolContaining(rawPtr);

                    pools[poolID]->deallocate(rawPtr, sizeof (T), n);
                }

                {
                    MemoryTrackerMutexType::scoped_lock lock(memoryTrackerMutex);
                    memoryTracker->trackDeallocation(ptr, BYTES_TO_DEALLOCATE);
                }
            }

#ifdef DEBUG
            void assertPoolIsUnique(const boost::shared_ptr<Pool>& pool);
#endif
        };

        /**
         * macros for making memory profiling easier to use
         */
#ifdef DEBUG
#define BEGIN_NEW_FRAME(mngr) mngr->beginNewFrame()
#else
#define BEGIN_NEW_FRAME(mngr)
#endif
    }
}

#endif	/* UTILITIES_MEMORY_MEMORYMANAGER_H */

