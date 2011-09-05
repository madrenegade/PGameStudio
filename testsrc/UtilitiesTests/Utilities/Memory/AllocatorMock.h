/* 
 * File:   AllocatorMock.h
 * Author: madrenegade
 *
 * Created on September 5, 2011, 2:40 PM
 */

#ifndef UTILITIES_MEMORY_ALLOCATORMOCK_H
#define	UTILITIES_MEMORY_ALLOCATORMOCK_H

#include "Utilities/Memory/Allocators/Allocator.h"

namespace Utilities
{
    namespace Memory
    {

        class AllocatorMock : public Allocator
        {
        public:
            AllocatorMock(size_t maxSize, size_t pageSize, size_t blockSize);
            
            virtual pointer allocate(size_t bytes);
            virtual void deallocate(const_pointer ptr, size_t sizeOfOneObject, size_t numObjects);
            
            virtual size_t getFreeMemory() const;
            
            virtual size_t getLargestFreeArea() const;
        };
    }
}


#endif	/* UTILITIES_MEMORY_ALLOCATORMOCK_H */

