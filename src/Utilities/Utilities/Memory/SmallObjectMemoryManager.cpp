#include "Utilities/Memory/SmallObjectMemoryManager.h"
#include "Utilities/Memory/OutOfMemoryException.h"
#include "Utilities/Memory/FixedPageSizePool.h"
#include "Utilities/Memory/constants.h"

namespace Utilities
{
    namespace Memory
    {
        SmallObjectMemoryManager::SmallObjectMemoryManager(size_t maxMemory, size_t defaultPageSize)
        : AbstractMemoryManager(maxMemory)
        {
            
        }
        
        void SmallObjectMemoryManager::createPool(size_t size, pool_id id)
        {
            if(size > getFreeMemory())
            {
                throw OutOfMemoryException();
            }
            
            poolManager.add(new FixedPageSizePool(size, 4 * KByte), id);
        }
    }
}
