/* 
 * File:   LargeObjectMemoryManager.cpp
 * Author: madrenegade
 * 
 * Created on August 31, 2011, 3:50 PM
 */

#include "Utilities/Memory/LargeObjectMemoryManager.h"
#include "Utilities/Memory/LargeObjectMemoryManager.h"
#include "Utilities/Memory/FixedPageSizePool.h"
#include "Utilities/Memory/OutOfMemoryException.h"
#include "Utilities/Memory/constants.h"

namespace Utilities
{
    namespace Memory
    {
        LargeObjectMemoryManager::LargeObjectMemoryManager(size_t maxMemory, size_t defaultPageSize)
        : AbstractMemoryManager(maxMemory)
        {
            
        }
        
        void LargeObjectMemoryManager::createPool(size_t size, pool_id id)
        {
            if(size > getFreeMemory())
            {
                throw OutOfMemoryException();
            }
            
            poolManager.add(new FixedPageSizePool(size, size / 4), id);
        }
    }
}


