/* 
 * File:   LargeObjectAllocator.h
 * Author: madrenegade
 *
 * Created on September 2, 2011, 11:00 PM
 */

#ifndef UTILITIES_MEMORY_LARGEOBJECTALLOCATOR_H
#define	UTILITIES_MEMORY_LARGEOBJECTALLOCATOR_H

#include "Utilities/Memory/Allocators/MediumObjectAllocator.h"

namespace Utilities
{
    namespace Memory
    {

        class LargeObjectAllocator : public MediumObjectAllocator
        {
        public:
            LargeObjectAllocator(const boost::shared_ptr<PageManager>& pageManager, const size_t blockSize);
            
//            virtual byte_pointer allocate(size_t bytes);
//            virtual void deallocate(const_byte_pointer ptr, size_t sizeOfOneObject, size_t numObjects);
//
//            virtual size_t getFreeMemory() const;
        };
    }
}

#endif	/* UTILITIES_MEMORY_LARGEOBJECTALLOCATOR_H */

