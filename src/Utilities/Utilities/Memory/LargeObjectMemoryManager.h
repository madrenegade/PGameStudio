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
            LargeObjectMemoryManager(size_t maxMemory, size_t defaultPageSize);
            
            virtual void createPool(size_t size, pool_id id);
        };
    }
}


#endif	/* UTILITIES_MEMORY_LARGEOBJECTMEMORYMANAGER_H */

