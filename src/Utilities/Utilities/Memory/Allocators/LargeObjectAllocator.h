/* 
 * File:   LargeObjectAllocator.h
 * Author: madrenegade
 *
 * Created on September 2, 2011, 11:00 PM
 */

#ifndef UTILITIES_MEMORY_LARGEOBJECTALLOCATOR_H
#define	UTILITIES_MEMORY_LARGEOBJECTALLOCATOR_H

#include "Utilities/Memory/Allocators/Allocator.h"

namespace Utilities
{
    namespace Memory
    {

        class LargeObjectAllocator : public Allocator
        {
        public:
            LargeObjectAllocator(size_t maxSize, size_t pageSize, size_t blockSize);
            
            virtual pointer allocate(size_t bytes);
            virtual void deallocate(const_pointer ptr, size_t sizeOfOneObject, size_t numObjects);

            virtual size_t getFreeMemory() const;
            
        protected:
            virtual size_t getLargestFreeArea() const;
        };
    }
}

#endif	/* UTILITIES_MEMORY_LARGEOBJECTALLOCATOR_H */

