/*
 * File:   Pool.h
 * Author: madrenegade
 *
 * Created on September 1, 2011, 4:27 PM
 */

#ifndef UTILITIES_MEMORY_POOL_H
#define	UTILITIES_MEMORY_POOL_H

#include <boost/scoped_array.hpp>
#include <boost/shared_ptr.hpp>

#include "Utilities/Memory/typedefs.h"
#include "Utilities/Memory/MemoryPoolSettings.h"
#include "Utilities/Memory/Allocators/SmallObjectAllocator.h"
#include "Utilities/Memory/Allocators/MediumObjectAllocator.h"
#include "Utilities/Memory/Allocators/LargeObjectAllocator.h"

namespace Utilities
{
    namespace Memory
    {
        /**
         * A memory pool using memory pages.
         */
        class Pool
        {
        public:
            typedef boost::shared_ptr<Pool> Ptr;

            /**
             * Create a new memory pool using the specified settings.
             * @param settings - The settings used to create the memory pool.
             * @return A smart pointer to the newly created memory pool.
             */
            static Ptr create(const MemoryPoolSettings& settings = MemoryPoolSettings());

            /**
             * Allocate the given amount of bytes.
             * @param bytes - The amount of bytes to allocate.
             * @return The pointer to the beginning of the allocated memory area.
             */
            byte_pointer allocate(const size_t bytes);

            /**
             * Deallocate a memory area.
             * @param ptr - The pointer to the beginning of the memory area to deallocate.
             * @param sizeOfOneObject - The size of one object in bytes.
             * @param numObjects - The number of objects to deallocate.
             */
            void deallocate(const_byte_pointer ptr, const size_t sizeOfOneObject, const size_t numObjects);

            /**
             * Get the current memory used by this pool.
             * @return The amount of used memory in bytes.
             */
            size_t getMemoryUsage() const;

            /**
             * Check if a pointer belongs to this pool.
             * @param ptr - The pointer to check.
             * @return True if the pointer belongs to this pool, false otherwise.
             */
            bool contains(const_byte_pointer ptr) const;

        private:
            Pool(const MemoryPoolSettings& settings);

            const MemoryPoolSettings settings;

            SmallObjectAllocator smallObjects;
            MediumObjectAllocator mediumObjects;
            LargeObjectAllocator largeObjects;

            Allocator* getAllocatorFor(const size_t bytes);
        };
    }
}


#endif	/* UTILITIES_MEMORY_POOL_H */

