#include "Utilities/Memory/MemoryTracker.h"

#include <glog/logging.h>

namespace Utilities
{
    namespace Memory
    {

        MemoryTracker::MemoryTracker()
        : memoryUsage(0)
        {
        }
        
        MemoryTracker::~MemoryTracker()
        {
        }

        size_t MemoryTracker::getMemoryUsage() const
        {
            return memoryUsage;
        }
        
        void MemoryTracker::logMemoryLeaks() const
        {
            const std::vector<AllocationInfo> dump(getMemoryDump());
            
            if(!dump.empty())
            {
                LOG(ERROR) << "Memory leaks detected: " << memoryUsage << " bytes in " << dump.size() << " blocks";
                
                 for(unsigned int i = 0; i < dump.size(); ++i)
                 {
                   const AllocationInfo& allocationInfo = dump.at(i);
                   
                     VLOG(1) << "Block information:" << std::endl
                        << "Address: " << reinterpret_cast<long>(allocationInfo.getPointer()) << std::endl
                        << "Size: " << allocationInfo.getSize() << std::endl
                        << "Type: " << allocationInfo.getType();
                 }
            }
        }
    }
}
