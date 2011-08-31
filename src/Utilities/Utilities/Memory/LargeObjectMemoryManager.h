/* 
 * File:   LargeObjectMemoryManager.h
 * Author: madrenegade
 *
 * Created on August 31, 2011, 3:50 PM
 */

#ifndef UTILITIES_MEMORY_LARGEOBJECTMEMORYMANAGER_H
#define	UTILITIES_MEMORY_LARGEOBJECTMEMORYMANAGER_H

#include "Utilities/Memory/AbstractMemoryManager.h"

namespace Utilities
{
    namespace Memory
    {

        class LargeObjectMemoryManager : public AbstractMemoryManager
        {
        public:
            LargeObjectMemoryManager(size_t maxMemory);
            
            virtual pointer allocate(size_t n, unsigned char prealloc);
			virtual void deallocate(const_pointer ptr, size_t sizeOfOne, size_t n);
        };
    }
}


#endif	/* UTILITIES_MEMORY_LARGEOBJECTMEMORYMANAGER_H */

