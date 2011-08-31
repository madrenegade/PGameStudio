#ifndef UTILITIES_MEMORY_SMALLOBJECTMEMORYMANAGER_H
#define UTILITIES_MEMORY_SMALLOBJECTMEMORYMANAGER_H

#include "Utilities/Memory/AbstractMemoryManager.h"

namespace Utilities
{
	namespace Memory
	{
	    class SmallObjectMemoryManager : public AbstractMemoryManager
	    {
        public:
            SmallObjectMemoryManager(size_t maxMemory);
            
            virtual pointer allocate(size_t n, unsigned char prealloc);
			virtual void deallocate(const_pointer ptr, size_t sizeOfOne, size_t n);
	    };
	}
}

#endif // UTILITIES_MEMORY_SMALLOBJECTMEMORYMANAGER_H
