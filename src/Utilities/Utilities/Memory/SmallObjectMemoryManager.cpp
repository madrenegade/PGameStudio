#include "Utilities/Memory/SmallObjectMemoryManager.h"

namespace Utilities
{
    namespace Memory
    {
        SmallObjectMemoryManager::SmallObjectMemoryManager(size_t maxMemory)
        : AbstractMemoryManager(maxMemory)
        {
            
        }
        
        pointer SmallObjectMemoryManager::allocate(size_t n, pool_id pool, char prealloc)
        {
        }
        
		void SmallObjectMemoryManager::deallocate(const_pointer ptr, size_t sizeOfOne, size_t n, pool_id pool)
        {
            
        }
    }
}
