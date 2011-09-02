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
        MemoryTrackerMock::~MemoryTrackerMock()
        {
            logMemoryLeaks();
        }
        
        void MemoryTrackerMock::trackAllocation(const_pointer ptr, size_t bytes, const std::type_info& type)
        {
            
        }
        
        void MemoryTrackerMock::trackDeallocation(const_pointer ptr, size_t bytes, const std::type_info& type)
        {
            
        }
        
        MemoryTracker::MemoryDump MemoryTrackerMock::getMemoryDump() const
        {
            MemoryDump dump;
            
            return dump;
        }
    }
}
