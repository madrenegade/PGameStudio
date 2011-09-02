/* 
 * File:   SmallObjectAllocator.h
 * Author: madrenegade
 *
 * Created on September 2, 2011, 10:55 PM
 */

#ifndef UTILITIES_MEMORY_SMALLOBJECTALLOCATOR_H
#define	UTILITIES_MEMORY_SMALLOBJECTALLOCATOR_H

#include "Utilities/Memory/Allocator.h"

namespace Utilities
{
    namespace Memory
    {

        class SmallObjectAllocator : public Allocator
        {
        public:
            SmallObjectAllocator(size_t maxSize, size_t pageSize, size_t blockSize);
            
            virtual pointer allocate(size_t bytes);
            virtual void deallocate(const_pointer ptr, size_t sizeOfOneObject, size_t numObjects);

        protected:
            virtual size_t getLargestFreeArea() const;
            virtual size_t getFreeMemory() const;
        };
    }
}


#endif	/* UTILITIES_MEMORY_SMALLOBJECTALLOCATOR_H */

