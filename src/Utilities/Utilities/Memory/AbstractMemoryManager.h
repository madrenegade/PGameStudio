#ifndef UTILITIES_MEMORY_ABSTRACTMANAGER_H
#define UTILITIES_MEMORY_ABSTRACTMANAGER_H

#include <typeinfo>
#include <glog/logging.h>

#include "Utilities/Memory/MemoryTracker.h"
#include "Utilities/Memory/PoolManager.h"
#include "Utilities/Memory/typedefs.h"

namespace Utilities
{
	namespace Memory
	{
		class AbstractMemoryManager
		{
		public:
			virtual ~AbstractMemoryManager();
            
            virtual void createPool(size_t size, pool_id id) = 0;
            
//			virtual pointer allocate(size_t n, pool_id pool = 0, char prealloc = 0) = 0;
//			virtual void deallocate(const_pointer ptr, size_t sizeOfOne, size_t n, pool_id = 0) = 0;
            
            const size_t getMaxMemory() const;
            
            virtual const size_t getFreeMemory() const;
            
            MemoryTracker* getTracker();
            
            PoolManager* getPoolManager();
            
		protected:
			AbstractMemoryManager(size_t maxMemory);
            
            void setMemory(pointer ptr, size_t n, char to) const;
            
            const size_t maxMemory;
            
            MemoryTracker memoryTracker;
            PoolManager poolManager;
            
            static const char PREALLOCATION_BYTE = 'a';
		};
	}
}

#endif // UTILITIES_MEMORY_ABSTRACTMANAGER_H
