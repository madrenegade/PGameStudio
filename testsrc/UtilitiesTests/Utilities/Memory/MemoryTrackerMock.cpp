/*
 * File:   MemoryTrackerMock.cpp
 * Author: madrenegade
 *
 * Created on September 2, 2011, 12:38 PM
 */

#include "Utilities/Memory/MemoryTrackerMock.h"

namespace Utilities
{
    namespace Memory
    {
        MemoryTrackerMock::MemoryTrackerMock()
            : allocations(0), deallocations(0)
        {

        }

        MemoryTrackerMock::~MemoryTrackerMock()
        {
            logMemoryLeaks();
        }

        unsigned int MemoryTrackerMock::getAllocations() const
        {
            return allocations;
        }

        unsigned int MemoryTrackerMock::getDeallocations() const
        {
            return deallocations;
        }

        void MemoryTrackerMock::trackAllocation(const char* const, const_byte_pointer /*ptr*/, size_t /*bytes*/, const std::type_info& /*type*/)
        {
            ++allocations;
        }

        void MemoryTrackerMock::trackDeallocation(const char* const, const_byte_pointer /*ptr*/, size_t /*bytes*/, const std::type_info& /*type*/)
        {
            ++deallocations;
        }

        MemoryTracker::MemoryDump MemoryTrackerMock::getMemoryDump() const
        {
            MemoryDump dump;

            return dump;
        }
    }
}
