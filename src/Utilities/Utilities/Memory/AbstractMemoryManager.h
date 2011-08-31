#ifndef UTILITIES_MEMORY_ABSTRACTMANAGER_H
#define UTILITIES_MEMORY_ABSTRACTMANAGER_H

#include <typeinfo>
#include "Utilities/Memory/MemoryTracker.h"

#include <glog/logging.h>

namespace Utilities
{
	namespace Memory
	{
		class AbstractMemoryManager
		{
		public:
            typedef unsigned char* pointer;
            typedef const unsigned char* const_pointer;
            
			virtual ~AbstractMemoryManager();
            
			virtual pointer allocate(size_t n, unsigned char prealloc) = 0;
			virtual void deallocate(const_pointer ptr, size_t sizeOfOne, size_t n) = 0;
            
            const size_t getMaxMemory() const;
            
            virtual const size_t getFreeMemory() const;
            
            MemoryTracker* getTracker();
            
		protected:
			AbstractMemoryManager(size_t maxMemory);
            
            void setMemory(unsigned char* ptr, size_t n, unsigned char to) const;
            
            const size_t maxMemory;
            
            MemoryTracker memoryTracker;
            
            static const unsigned char PREALLOCATION_BYTE = 'a';
		};
	}
}

#endif // UTILITIES_MEMORY_ABSTRACTMANAGER_H
