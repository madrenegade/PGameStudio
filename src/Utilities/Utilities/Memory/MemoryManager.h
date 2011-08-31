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

namespace Utilities
{
    namespace Memory
    {

        class MemoryManager : public AbstractMemoryManager
        {
        public:
            MemoryManager(size_t threshold, size_t maxMemoryForSmallObjects, size_t maxMemoryForLargeObjects);

            template<typename T>
            T* allocate(size_t n)
            {
                const size_t BYTES_TO_ALLOCATE = n * sizeof (T);

                VLOG(1) << "Allocating " << BYTES_TO_ALLOCATE << " bytes";

#ifdef DEBUG
                void* ptr = allocate(BYTES_TO_ALLOCATE, PREALLOCATION_BYTE);
#else
                pointer ptr = allocate(BYTES_TO_ALLOCATE, 0);
#endif

                VLOG(1) << "Allocated " << BYTES_TO_ALLOCATE << " bytes";

                getTrackerFor(BYTES_TO_ALLOCATE)->trackAllocation(ptr, BYTES_TO_ALLOCATE, typeid (T));

                return reinterpret_cast<T*> (ptr);
            }

            template<typename T>
            void deallocate(const T* ptr, size_t n)
            {
                const size_t BYTES_TO_DEALLOCATE = n * sizeof (T);

                VLOG(1) << "Deallocating " << BYTES_TO_DEALLOCATE << " bytes";

                deallocate(reinterpret_cast<const_pointer> (ptr), sizeof (T), n);

                VLOG(1) << "Deallocated " << BYTES_TO_DEALLOCATE << " bytes";

                getTrackerFor(BYTES_TO_DEALLOCATE)->trackDeallocation(ptr, BYTES_TO_DEALLOCATE, typeid (T));
            }
            
            virtual const size_t getFreeMemory() const;

        protected:
            virtual pointer allocate(size_t n, unsigned char prealloc);
            virtual void deallocate(const_pointer ptr, size_t sizeOfOne, size_t n);

        private:
            const size_t threshold;

            SmallObjectMemoryManager smallObjects;
            LargeObjectMemoryManager largeObjects;
            
            MemoryTracker* getTrackerFor(size_t bytes);
        };
    }
}

#endif	/* UTILITIES_MEMORY_MEMORYMANAGER_H */

