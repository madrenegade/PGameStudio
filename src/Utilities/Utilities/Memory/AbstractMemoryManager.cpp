#include <stdexcept>

#include "Utilities/Memory/AbstractMemoryManager.h"
#include "MemoryManager.h"

namespace Utilities
{
    namespace Memory
    {
        AbstractMemoryManager::AbstractMemoryManager(size_t maxMemory)
        : maxMemory(maxMemory)
        {
            if(maxMemory == 0)
            {
                throw std::invalid_argument("maxMemory");
            }
        }

        AbstractMemoryManager::~AbstractMemoryManager()
        {
        }
        
        const size_t AbstractMemoryManager::getFreeMemory() const
        {
            VLOG_EVERY_N(1, 1) << "Free memory: " << maxMemory - memoryTracker.getAllocatedMemorySize() << " bytes";
                
            return maxMemory - memoryTracker.getAllocatedMemorySize();
        }
     
        const size_t AbstractMemoryManager::getMaxMemory() const
        {
            return maxMemory;
        }
        
        MemoryTracker* AbstractMemoryManager::getTracker()
        {
            return &memoryTracker;
        }
        
        PoolManager* AbstractMemoryManager::getPoolManager()
        {
            return &poolManager;
        }
        
        void AbstractMemoryManager::setMemory(pointer ptr, size_t n, char to) const
        {
            for(int i = 0; i < n; ++i)
            {
                ptr[i] = to;
            }
        }
        
    }
}
