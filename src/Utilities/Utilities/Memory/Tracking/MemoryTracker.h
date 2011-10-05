#ifndef UTILITIES_MEMORY_MEMORYTRACKER_H
#define UTILITIES_MEMORY_MEMORYTRACKER_H

#include <vector>
#include <memory>
#include "Utilities/Memory/AllocationInfo.h"

namespace Utilities
{
    namespace Memory
    {
        /**
         * A helper class for tracking memory allocations and deallocations.
         */
        class MemoryTracker
        {
        public:
            typedef std::shared_ptr<MemoryTracker> Ptr;
            typedef std::vector<AllocationInfo> MemoryDump;

            virtual ~MemoryTracker();

            /**
             * Track an allocation.
             * @param ptr - The pointer used for the allocation.
             * @param bytes - The number of bytes allocated.
             */
            template<typename T>
            void trackAllocation(const char* const pool, T* ptr, const size_t bytes)
            {
                trackAllocation(pool, reinterpret_cast<const_byte_pointer>(ptr), bytes, typeid(T));
                memoryUsage += bytes;

                if(memoryUsage > maxMemoryUsage)
                {
                    maxMemoryUsage = memoryUsage;
                }
            }

            /**
             * Track a deallocation.
             * @param ptr - The pointer used for the deallocation.
             * @param bytes - The number of bytes deallocated.
             */
            template<typename T>
            void trackDeallocation(const char* const pool, const T* ptr, const size_t bytes)
            {
                trackDeallocation(pool, reinterpret_cast<const_byte_pointer>(ptr), bytes, typeid(T));
                memoryUsage -= bytes;
            }

            size_t getMemoryUsage() const;
            size_t getMaxMemoryUsage() const;

            /**
             * Log memory leaks to the console. This prints out all allocations where no
             * deallocation has been done.
             */
            void logMemoryLeaks() const;

            /**
             * Get a dump of current memory.
             */
            virtual MemoryDump getMemoryDump() const = 0;

            void printMemoryDump() const;

        protected:
            MemoryTracker();

            virtual void trackAllocation(const char* const pool, const_byte_pointer ptr, const size_t bytes, const std::type_info& type) = 0;
            virtual void trackDeallocation(const char* const pool, const_byte_pointer ptr, const size_t bytes, const std::type_info& type) = 0;

        private:
            size_t memoryUsage;
            size_t maxMemoryUsage;
        };
    }
}

#endif // UTILITIES_MEMORY_MEMORYTRACKER_H
