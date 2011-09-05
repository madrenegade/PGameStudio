#include "Utilities/Memory/MemoryTracker.h"

#include <glog/logging.h>
#include <glog/raw_logging.h>

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
                RAW_LOG_WARNING("Memory leaks detected: %i bytes in %i blocks", memoryUsage, dump.size());
                
                 for(unsigned int i = 0; i < dump.size(); ++i)
                 {
                   const AllocationInfo& allocationInfo = dump.at(i);
                   
                   RAW_VLOG(1, "Block information:\nAddress: %i\nSize: %i\nType: %s", 
                       reinterpret_cast<long>(allocationInfo.getPointer()), 
                       allocationInfo.getSize(), allocationInfo.getType().c_str());
                 }
            }
        }
    }
}
