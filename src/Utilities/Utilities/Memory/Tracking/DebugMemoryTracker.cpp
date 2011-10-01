/*
 * File:   DebugMemoryTracker.cpp
 * Author: madrenegade
 *
 * Created on September 2, 2011, 1:55 PM
 */

#include "Utilities/Memory/Tracking/DebugMemoryTracker.h"
#include "Utilities/Memory/Exceptions/AllocationException.h"
#include "Utilities/functions.h"

#include <glog/logging.h>
#include <glog/raw_logging.h>

namespace Utilities
{
    namespace Memory
    {

        void DebugMemoryTracker::trackAllocation(const char* const pool, const_byte_pointer ptr, const size_t bytes, const std::type_info& type)
        {
            if(allocations.find(ptr) != allocations.end())
            {
                AllocationInfo info(allocations.at(ptr));
                LOG(INFO) << "Address: " << reinterpret_cast<const void*>(info.getPointer());
                LOG(INFO) << "Size: " << info.getSize();
                LOG(INFO) << "Type: " << info.getType();
                LOG(INFO) << "Pool: " << info.getPool();
                throw AllocationException("Pointer already in use");
            }

            if(bytes == 0)
            {
                throw AllocationException("Allocating zero bytes is not allowed");
            }

            AllocationInfo allocationInfo(pool, ptr, bytes, type);
            allocations[ptr] = allocationInfo;
        }

        void DebugMemoryTracker::trackDeallocation(const char* const pool, const_byte_pointer ptr, const size_t bytes, const std::type_info& type)
        {
            if(allocations.find(ptr) == allocations.end())
            {
                throw AllocationException("Deallocate failed because pointer is not tracked");
            }

            const AllocationInfo actual(pool, ptr, bytes, type);
            const AllocationInfo expected(allocations[ptr]);

            if(expected.getPool() != actual.getPool())
            {
                throw AllocationException("Deallocate failed because pools do not match");
            }

            if(expected.getSize() != actual.getSize())
            {
                throw AllocationException("Deallocate failed because sizes do not match");
            }

            if(expected.getType() != actual.getType())
            {
                RAW_LOG_ERROR("Expected type '%s' but found '%s'", expected.getType().c_str(), actual.getType().c_str());

                throw AllocationException("Deallocate failed because types do not match");
            }

            allocations.erase(allocations.find(ptr));
        }

        MemoryTracker::MemoryDump DebugMemoryTracker::getMemoryDump() const
        {
            MemoryDump dump(allocations.size());

            unsigned int index = 0;
            for(auto i = allocations.begin(); i != allocations.end(); ++i)
            {
                dump[index] = i->second;
                ++index;
            }

            return dump;
        }
    }
}

