/* 
 * File:   DebugMemoryTracker.cpp
 * Author: madrenegade
 * 
 * Created on September 2, 2011, 1:55 PM
 */

#include "Utilities/Memory/DebugMemoryTracker.h"
#include "Utilities/Memory/AllocationException.h"
#include "Utilities/functions.h"

#include <glog/logging.h>
#include <glog/raw_logging.h>

namespace Utilities
{
    namespace Memory
    {

        void DebugMemoryTracker::trackAllocation(const_pointer ptr, size_t bytes, const std::type_info& type)
        {
            if(allocations.find(ptr) != allocations.end())
            {
                throw AllocationException("Pointer already in use");
            }
            
            if(bytes == 0)
            {
                throw AllocationException("Allocating zero bytes is not allowed");
            }
            
            AllocationInfo allocationInfo(ptr, bytes, type);
            allocations[ptr] = allocationInfo;
        }

        void DebugMemoryTracker::trackDeallocation(const_pointer ptr, size_t bytes, const std::type_info& type)
        {
            if(allocations.find(ptr) == allocations.end())
            {
                throw AllocationException("Deallocate failed because pointer is not tracked");
            }
            
            AllocationInfo actual(ptr, bytes, type);
            
            AllocationInfo expected(allocations[ptr]);
            
            if(expected.getSize() != actual.getSize())
            {
                throw AllocationException("Deallocate failed because sizes do not match");
            }
            
            if(expected.getType() != actual.getType())
            {
                RAW_LOG_INFO("Expected type '%s' but found '%s'", expected.getType().c_str(), actual.getType().c_str());
                
                throw AllocationException("Deallocate failed because types do not match");
            }
        }

        MemoryTracker::MemoryDump DebugMemoryTracker::getMemoryDump() const
        {
            
        }
    }
}

