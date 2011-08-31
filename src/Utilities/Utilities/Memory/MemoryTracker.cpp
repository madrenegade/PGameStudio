#include "Utilities/Memory/MemoryTracker.h"
#include "AbstractMemoryManager.h"
#include "AllocationException.h"
#include "MemoryManager.h"
#include <glog/logging.h>

namespace Utilities
{
    namespace Memory
    {

        MemoryTracker::MemoryTracker()
        : memorySize(0)
        {

        }
        
        MemoryTracker::~MemoryTracker()
        {
            if(memorySize > 0)
            {
                if(blocks.size() == 1)
                {
                    LOG(ERROR) << "1 memory leak detected (" << memorySize << " bytes)";
                }
                else
                {
                   LOG(ERROR) << blocks.size() << " memory leaks detected (" << memorySize << " bytes)"; 
                }
                
                for(BlockMap::const_iterator i = blocks.begin(); i != blocks.end(); ++i)
                {
                    const AllocationInfo& allocationInfo(i->second);
                    
                    VLOG(1) << "Memory leak information" << std::endl
                        << "Address " << allocationInfo.getPointer() << std::endl
                        << "Size: " << allocationInfo.getSize() << std::endl
                        << "Type: " << allocationInfo.getType();
                }
            }
        }

        void MemoryTracker::trackAllocation(void* ptr, size_t bytes, const std::type_info& type)
        {
            verifyUnused(ptr);

            if (bytes == 0)
            {
                throw AllocationException();
            }

            AllocationInfo allocationInfo(ptr, bytes, type);

            blocks[ptr] = allocationInfo;

            memorySize += bytes;
        }

        void MemoryTracker::trackDeallocation(void* ptr, size_t bytes, const std::type_info& type)
        {
            verify(ptr, bytes, type);

            blocks.erase(blocks.find(ptr));

            memorySize -= bytes;
        }

        size_t MemoryTracker::getAllocatedMemorySize() const
        {
            return memorySize;
        }

        void MemoryTracker::verifyUnused(void* ptr) const
        {
            if (isTracked(ptr))
            {
                const AllocationInfo allocationInfo(blocks.at(ptr));

                LOG(ERROR) << "Address " << ptr << " already in use" << std::endl
                    << "Size: " << allocationInfo.getSize() << std::endl
                    << "Type: " << allocationInfo.getType();

                throw AllocationException();
            }
        }

        void MemoryTracker::verify(void* ptr, size_t bytes, const std::type_info& type) const
        {
            const AllocationInfo actual(AllocationInfo(ptr, bytes, type));
            
            assertThatPointerIsTracked(actual);
            
            const AllocationInfo expected(blocks.at(ptr));
            
            assertDetailsMatch(expected, actual);
        }

        void MemoryTracker::assertThatPointerIsTracked(const AllocationInfo& actual) const
        {
            if (!isTracked(actual.getPointer()))
            {
                LOG(ERROR) << "Invalid deallocation" << std::endl
                    << "Address: " << actual.getPointer() << " (invalid)" << std::endl
                    << "Size: " << actual.getSize() << std::endl
                    << "Type: " << actual.getType();

                throw AllocationException();
            }
        }

        void MemoryTracker::assertDetailsMatch(const AllocationInfo& expected, const AllocationInfo& actual) const
        {
            if (actual.getSize() != expected.getSize())
            {
                LOG(ERROR) << "Invalid deallocation" << std::endl
                    << "Address: " << actual.getPointer() << std::endl
                    << "Size: " << actual.getSize() << " (expected " << expected.getSize() << ")" << std::endl
                    << "Type: " << actual.getType();

                throw AllocationException();
            }

            if (actual.getType() != expected.getType())
            {
                LOG(ERROR) << "Invalid deallocation" << std::endl
                    << "Address: " << actual.getPointer() << std::endl
                    << "Size: " << actual.getSize() << std::endl
                    << "Type: " << actual.getType() << " (expected " << expected.getType() << ")";

                throw AllocationException();
            }
        }

        bool MemoryTracker::isTracked(const void* ptr) const
        {
            return blocks.find(ptr) != blocks.end();
        }
    }
}
