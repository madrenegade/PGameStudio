/* 
 * File:   MediumObjectAllocator.h
 * Author: madrenegade
 *
 * Created on September 2, 2011, 10:59 PM
 */

#ifndef UTILITIES_MEMORY_MEDIUMOBJECTALLOCATOR_H
#define	UTILITIES_MEMORY_MEDIUMOBJECTALLOCATOR_H

#include "Utilities/Memory/Allocators/Allocator.h"

namespace Utilities
{
    namespace Memory
    {

        class MediumObjectAllocator : public Allocator
        {
        public:
            MediumObjectAllocator(size_t maxSize, size_t pageSize, size_t blockSize);
            
            virtual pointer allocate(size_t bytes);
            virtual void deallocate(const_pointer ptr, size_t sizeOfOneObject, size_t numObjects);

            virtual size_t getFreeMemory() const;
            
        protected:
            virtual size_t getLargestFreeArea() const;
        };
    }
}

#endif	/* UTILITIES_MEMORY_MEDIUMOBJECTALLOCATOR_H */

