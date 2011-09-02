/* 
 * File:   DebugMemoryTracker.cpp
 * Author: madrenegade
 * 
 * Created on September 2, 2011, 1:55 PM
 */

#include "Utilities/Memory/DebugMemoryTracker.h"

namespace Utilities
{
    namespace Memory
    {

        void DebugMemoryTracker::trackAllocation(const_pointer ptr, size_t bytes, const std::type_info& type)
        {

        }

        void DebugMemoryTracker::trackDeallocation(const_pointer ptr, size_t bytes, const std::type_info& type)
        {
            
        }

        MemoryTracker::MemoryDump DebugMemoryTracker::getMemoryDump() const
        {
            
        }
    }
}

