#include "Utilities/Memory/Tracking/MemoryTracker.h"

#include <glog/logging.h>
#include <glog/raw_logging.h>
#include <fstream>

namespace Utilities
{
    namespace Memory
    {

        MemoryTracker::MemoryTracker()
            : memoryUsage(0), maxMemoryUsage(0)
        {
        }

        MemoryTracker::~MemoryTracker()
        {
        }

        size_t MemoryTracker::getMemoryUsage() const
        {
            return memoryUsage;
        }

        size_t MemoryTracker::getMaxMemoryUsage() const
        {
            return maxMemoryUsage;
        }

        void MemoryTracker::logMemoryLeaks() const
        {
            const std::vector<AllocationInfo> dump(getMemoryDump());

            if (!dump.empty())
            {
                RAW_LOG_WARNING("Memory leaks detected: %li bytes in %li blocks", memoryUsage, dump.size());

                for (unsigned int i = 0; i < dump.size(); ++i)
                {
                    const AllocationInfo& allocationInfo = dump.at(i);

                    RAW_VLOG(2, "Block information:\nAddress: %p\nSize: %li\nType: %s\nPool: %s",
                             allocationInfo.getPointer(),
                             allocationInfo.getSize(),
                             allocationInfo.getType().c_str(),
                             allocationInfo.getPool());
                }
            }
        }

        void MemoryTracker::printMemoryDump() const
        {
            const std::vector<AllocationInfo> dump(getMemoryDump());

            std::ofstream out("memorydump.txt");

            for (unsigned int i = 0; i < dump.size(); ++i)
            {
                const AllocationInfo& allocationInfo = dump.at(i);

//                RAW_LOG_INFO("Block information:\nAddress: %p\nSize: %li\nType: %s\nPool: %s",
//                             allocationInfo.getPointer(),
//                             allocationInfo.getSize(),
//                             allocationInfo.getType().c_str(),
//                             allocationInfo.getPool());

                out << "Block information:" << std::endl
                << "Address: " << reinterpret_cast<const void*>(allocationInfo.getPointer()) << std::endl
                << "Size: " << allocationInfo.getSize() << std::endl
                << "Type: " << allocationInfo.getType().c_str() << std::endl
                << "Pool: " << allocationInfo.getPool() << std::endl;
            }
        }
    }
}
