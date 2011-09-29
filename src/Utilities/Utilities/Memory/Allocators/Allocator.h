/*
 * File:   Allocator.h
 * Author: madrenegade
 *
 * Created on September 2, 2011, 10:49 PM
 */

#ifndef UTILITIES_MEMORY_ALLOCATOR_H
#define	UTILITIES_MEMORY_ALLOCATOR_H

#include "Utilities/Memory/typedefs.h"

#include <map>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <unordered_map>
#include <vector>

namespace Utilities
{
    namespace Memory
    {
        class PageManager;

        /**
         * Base class for allocators used by \ref Utilities::Memory::Pool.
         */
        class Allocator
        {
        public:
            /**
             * Allocate memory
             * @param bytes - The amount of bytes to allocate
             * @return A pointer to the begin of the allocated memory area.
             */
            virtual byte_pointer allocate(const size_t bytes) = 0;

            /**
             * Deallocate memory.
             * @param ptr - The pointer to the beginning of the memory area to deallocate.
             * @param sizeOfOneObject - The size of one object in bytes.
             * @param numObjects - The number of objects to deallocate.
             */
            virtual void deallocate(const_byte_pointer ptr, const size_t sizeOfOneObject, const size_t numObjects) = 0;

            /**
             * Check if a pointer has been allocated by this instance.
             * @param ptr - The pointer to check.
             * @return True if the pointer has been allocated by this instance, false otherwise.
             */
            bool contains(const_byte_pointer ptr) const;

            /**
             * Get the current memory allocated by this instance.
             * @return The amount of allocated memory in bytes.
             */
            size_t getMemoryUsage() const;

            /**
             * Get the amount of free memory.
             * @return The amount of memory in bytes which may be allocated using this instance.
             */
            virtual size_t getFreeMemory() const = 0;

        protected:
            Allocator(const boost::shared_ptr<PageManager>& pageManager, const size_t blockSize);

            const boost::shared_ptr<PageManager> pageManager;

            size_t memoryUsage;

            const size_t BLOCK_SIZE;
        };
    }
}

#endif	/* UTILITIES_MEMORY_ALLOCATOR_H */

