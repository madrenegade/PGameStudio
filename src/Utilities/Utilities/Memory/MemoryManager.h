/*
 * File:   MemoryManager.h
 * Author: madrenegade
 *
 * Created on August 31, 2011, 3:34 PM
 */

#ifndef UTILITIES_MEMORY_MEMORYMANAGER_H
#define	UTILITIES_MEMORY_MEMORYMANAGER_H


#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/static_assert.hpp>

#include <glog/logging.h>
#include <glog/raw_logging.h>
#include <map>
#include <stdexcept>

#include "Utilities/Memory/typedefs.h"
#include "Utilities/Memory/Pool.h"
#include "Utilities/Memory/Tracking/MemoryTracker.h"
#include "Utilities/Memory/ComposedDeleter.h"
#include "Utilities/functions.h"

#include <tbb/concurrent_hash_map.h>
#include <tbb/atomic.h>
#include <tbb/spin_mutex.h>
#include <tbb/spin_rw_mutex.h>

#ifdef DEBUG
#include "../MemoryProfiler/memprof/memprof/client.h"
#include "StackTrace.h"
#include "Utilities/Memory/Exceptions/AllocationException.h"
#endif

namespace Utilities
{
    namespace Memory
    {
#ifdef DEBUG
#define STACKTRACE_PARAM , const StackTrace& stacktrace = StackTrace()
#define STACKTRACE , stacktrace
#else
#define STACKTRACE_PARAM
#define STACKTRACE
#endif

        class MemoryManager
        {
        public:
            typedef std::shared_ptr<MemoryManager> Ptr;

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
            pool_id registerMemoryPool(const std::shared_ptr<Pool>& pool);

            /**
             * unregisters the memory pool
             * if the memory manager holds the last reference the pool will be deleted
             * @param poolID
             */
            void unregisterMemoryPool(const pool_id poolID);

            /**
             * Get the amount of memory in bytes used at the moment.
             * @return
             */
            size_t getMemoryUsage() const;

            /**
             * Construct the given object in the given memory pool using a custom pre-deleter.
             * The pre-deleter is called right before deallocation and may be used for clean up.
             *
             * @param obj - the object to place in the pool
             * @param preDeleter - the pre-deleter
             * @param poolID - the pool to place the object in
             * @return a pointer to the constructed object
             */
            template<typename T, typename Deleter>
            std::shared_ptr<T> construct(const T& obj, const Deleter& preDeleter, const pool_id poolID = 0
                                           STACKTRACE_PARAM)
            {
                // combine deleter with deallocation function
                typedef boost::function<void (T*)> MainDeleter;
                const MainDeleter mainDeleter = boost::bind(&MemoryManager::deallocate<T>, this, _1, 1);
                const ComposedDeleter<T, Deleter, MainDeleter> deleter(preDeleter, mainDeleter);

                std::shared_ptr<T> ptr(new (internalAllocate<T > (1, poolID STACKTRACE)) T(obj), deleter);

                return ptr;
            }

            /**
             * Construct the given object in the given memory pool.
             * Make sure that the memory manager instance exists when the ptr gets deleted.
             *
             * @param obj - the object to place in the pool
             * @param poolID - the pool to place the object in
             * @return a pointer to the constructed object
             */
            template<typename T>
            std::shared_ptr<T> construct(const T& obj, const pool_id poolID = 0
                                           STACKTRACE_PARAM)
            {
                std::shared_ptr<T> ptr(new (internalAllocate<T > (1, poolID STACKTRACE)) T(obj), boost::bind(&MemoryManager::deallocate<T>, this, _1, 1));

                return ptr;
            }

            template<typename T>
            boost::shared_array<T> allocate(const size_t numObjects, const pool_id poolID = 0
                                            STACKTRACE_PARAM)
            {
                DCHECK(numObjects > 1);

                boost::shared_array<T> ptr(internalAllocate<T> (numObjects, poolID STACKTRACE), boost::bind(&MemoryManager::deallocate<T>, this, _1, numObjects));

                return ptr;
            }

            /**
             * Allocation without using smart pointers.
             * This function is intended for use with external libraries
             * that can swap out their memory management functions.
             * @param numObjects
             * @param poolID
             * @param stacktrace
             * @return
             */
            template<typename T>
            T* rawAllocate(const size_t numObjects
                           STACKTRACE_PARAM, const pool_id poolID = 0)
            {
                return internalAllocate<T>(numObjects, poolID STACKTRACE);
            }

            template<typename T>
            void rawDeallocate(const T* ptr, const size_t n)
            {
                const size_t BYTES_TO_DEALLOCATE = n * sizeof (T);

                const_byte_pointer rawPtr = reinterpret_cast<const_byte_pointer> (ptr);

                pool_id poolID = 0;
                {
                    PoolMapMutexType::scoped_lock lock(poolMapMutex, true);
                    poolID = findPoolContaining(rawPtr);

                    pools[poolID]->deallocate(rawPtr, sizeof (T), n);
                }

                {
                    MemoryTrackerMutexType::scoped_lock lock(memoryTrackerMutex);
                    memoryTracker->trackDeallocation(pools[poolID]->getName(), ptr, BYTES_TO_DEALLOCATE);
                }
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

            ~MemoryManager();

        private:
            MemoryManager(const std::shared_ptr<MemoryTracker>& memoryTracker);

            typedef tbb::spin_mutex MemoryTrackerMutexType;
            MemoryTrackerMutexType memoryTrackerMutex;
            std::shared_ptr<MemoryTracker> memoryTracker;

            typedef tbb::spin_rw_mutex PoolMapMutexType;
            typedef std::map<pool_id, std::shared_ptr<Pool > > PoolMap;

            PoolMapMutexType poolMapMutex;
            PoolMap pools;

            tbb::atomic<pool_id> latestPoolID;

#ifdef DEBUG
            typedef tbb::spin_mutex ProfilerClientMutexType;
            ProfilerClientMutexType profilerClientMutex;
            std::unique_ptr<memprof::client> profilerClient;
#endif

            pool_id findPoolContaining(const_byte_pointer ptr) const;

            /**
             * allocate space for a bunch of objects
             * @param numObjects - the amount of objects to allocate space for
             * @param poolID - the pool in which the space should be allocated
             * @return a pointer to the beginning of the allocated space
             */
            template<typename T>
            T* internalAllocate(const size_t numObjects, const pool_id poolID = 0
                                STACKTRACE_PARAM)
            {
                const size_t BYTES_TO_ALLOCATE = numObjects * sizeof (T);

#ifdef DEBUG
                {
                    ProfilerClientMutexType::scoped_lock lock(profilerClientMutex);
                    profilerClient->send_allocation_info(stacktrace, numObjects* sizeof (T), poolID);
                }

                if (pools.find(poolID) == pools.end())
                {
                    throw std::logic_error("Invalid pool id");
                }

//                RAW_VLOG(4, "Allocating %li bytes for %li objects of type %s in pool '%s'",
//                         BYTES_TO_ALLOCATE, numObjects,
//                         Utilities::demangle(typeid (T).name()).c_str(), pools[poolID]->getName());
#endif

                T* ptr = 0;
                {
                    PoolMapMutexType::scoped_lock lock(poolMapMutex, true);

#ifdef DEBUG
                    try
                    {
                        byte_pointer rawPtr = pools[poolID]->allocate(BYTES_TO_ALLOCATE);

                        fillMemory(rawPtr, BYTES_TO_ALLOCATE, ALLOCATED);

                        ptr = reinterpret_cast<T*> (rawPtr);

                        //RAW_VLOG(4, "Allocated %lu bytes at address %p in pool %i (%p)", BYTES_TO_ALLOCATE, reinterpret_cast<void*> (ptr), poolID, reinterpret_cast<void*> (pools[poolID].get()));
                    }
                    catch(const std::exception& e)
                    {
                        RAW_LOG_ERROR("Allocation of %lu bytes for %li objects of type %s in pool '%s' failed\n%s",
                                      BYTES_TO_ALLOCATE, numObjects,
                                      Utilities::demangle(typeid (T).name()).c_str(),
                                      pools[poolID]->getName(), e.what());

                        throw;
                    }
#else
                    ptr = reinterpret_cast<T*> (pools[poolID]->allocate(BYTES_TO_ALLOCATE));
#endif
                }

                {
#ifdef DEBUG
                    try
                    {
#endif
                        MemoryTrackerMutexType::scoped_lock lock(memoryTrackerMutex);
                        memoryTracker->trackAllocation(pools[poolID]->getName(), ptr, BYTES_TO_ALLOCATE);
#ifdef DEBUG
                    }
                    catch(const AllocationException& e)
                    {
                        RAW_LOG_WARNING("The memory tracker found a problem\nAllocation details:\nBytes: %lu\nObjects: %li\nType: %s\nAddress: %p\nPool: '%s'\nProblem description: %s",
                                        BYTES_TO_ALLOCATE, numObjects,
                                        Utilities::demangle(typeid (T).name()).c_str(),
                                        reinterpret_cast<const void*> (ptr),
                                        pools[poolID]->getName(), e.what());
                        memoryTracker->printMemoryDump();

                        throw;
                    }
#endif
                }

                return ptr;
            }

            /**
             * deallocate space for a bunch of objects
             * @param ptr - the starting address of the space to deallocate
             * @param n - the amount of objects to determine how much space must be deallocated
             */
            template<typename T>
            void deallocate(const T* ptr, const size_t n)
            {
                const size_t BYTES_TO_DEALLOCATE = n * sizeof (T);

#ifdef DEBUG
//                RAW_VLOG(4, "Deallocating %lu bytes (address: %p, %lu objects of type %s)", BYTES_TO_DEALLOCATE, reinterpret_cast<const void*> (ptr), n, demangle(typeid (T).name()).c_str());
#endif

                for (size_t i = 0; i < n; ++i)
                {
                    ptr[i].~T();
                }

                const_byte_pointer rawPtr = reinterpret_cast<const_byte_pointer> (ptr);

                pool_id poolID = 0;
                {
                    PoolMapMutexType::scoped_lock lock(poolMapMutex, true);
                    poolID = findPoolContaining(rawPtr);

                    pools[poolID]->deallocate(rawPtr, sizeof (T), n);
                }

                {
                    MemoryTrackerMutexType::scoped_lock lock(memoryTrackerMutex);
                    memoryTracker->trackDeallocation(pools[poolID]->getName(), ptr, BYTES_TO_DEALLOCATE);
                }
            }

#ifdef DEBUG
            void assertPoolIsUnique(const std::shared_ptr<Pool>& pool);
#endif

            static void verifyPlatformAssumptions();
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

