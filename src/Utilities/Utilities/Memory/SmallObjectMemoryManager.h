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
            SmallObjectMemoryManager(size_t maxMemory, size_t defaultPageSize);
            
            virtual void createPool(size_t size, pool_id id);     
        };
    }
}

#endif // UTILITIES_MEMORY_SMALLOBJECTMEMORYMANAGER_H
