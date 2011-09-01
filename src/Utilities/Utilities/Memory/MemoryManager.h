/* 
 * File:   MemoryManager.h
 * Author: madrenegade
 *
 * Created on August 31, 2011, 3:34 PM
 */

#ifndef UTILITIES_MEMORY_MEMORYMANAGER_H
#define	UTILITIES_MEMORY_MEMORYMANAGER_H

#include "Utilities/Memory/AbstractMemoryManager.h"
#include "Utilities/Memory/SmallObjectMemoryManager.h"
#include "Utilities/Memory/LargeObjectMemoryManager.h"
#include "Utilities/Memory/MemoryManagerSettings.h"

namespace Utilities
{
    namespace Memory
    {

        class MemoryManager : public AbstractMemoryManager
        {
        public:
            MemoryManager(const MemoryManagerSettings& settings);
            
            pool_id createPoolForSmallObjects(size_t size);
            pool_id createPoolForLargeObjects(size_t size);
            
            template<typename T>
            T* construct(const T& obj, pool_id pool = 0)
            {
                return new (allocate<T>(1, pool)) T(obj);
            }

            template<typename T>
            T* allocate(size_t n, pool_id pool = 0)
            {
                const size_t BYTES_TO_ALLOCATE = n * sizeof (T);

                VLOG(1) << "Allocating " << BYTES_TO_ALLOCATE << " bytes in pool " << pool;

#ifdef DEBUG
                pointer rawPtr = allocate(BYTES_TO_ALLOCATE, pool, PREALLOCATION_BYTE);
#else
                pointer rawPtr = allocate(BYTES_TO_ALLOCATE, pool);
#endif

                VLOG(1) << "Allocated " << BYTES_TO_ALLOCATE << " bytes from pool " << pool;
                
                T* ptr = reinterpret_cast<T*> (rawPtr);

                getTrackerFor(BYTES_TO_ALLOCATE)->trackAllocation(ptr, BYTES_TO_ALLOCATE);

                return ptr;
            }

            template<typename T>
            void deallocate(const T* ptr, size_t n, pool_id pool = 0)
            {
                const size_t BYTES_TO_DEALLOCATE = n * sizeof (T);

                VLOG(1) << "Deallocating " << BYTES_TO_DEALLOCATE << " bytes from pool " << pool;

                deallocate(reinterpret_cast<const_pointer> (ptr), sizeof (T), n, pool);

                VLOG(1) << "Deallocated " << BYTES_TO_DEALLOCATE << " bytes from pool " << pool;

                getTrackerFor(BYTES_TO_DEALLOCATE)->trackDeallocation(ptr, BYTES_TO_DEALLOCATE);
            }
            
            virtual const size_t getFreeMemory() const;

        protected:
            virtual void createPool(size_t size, pool_id pool);
            
            pointer allocate(size_t bytes, pool_id pool, char prealloc = 0);
            void deallocate(const_pointer ptr, size_t sizeOfOne, size_t n, pool_id pool);

        private:
            const MemoryManagerSettings settings;

            SmallObjectMemoryManager smallObjects;
            LargeObjectMemoryManager largeObjects;
            
            AbstractMemoryManager* getManagerFor(size_t bytes);
            MemoryTracker* getTrackerFor(size_t bytes);
            
            pool_id newestPool;
        };
    }
}

#endif	/* UTILITIES_MEMORY_MEMORYMANAGER_H */

