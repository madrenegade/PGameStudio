/* 
 * File:   DebugMemoryTracker.h
 * Author: madrenegade
 *
 * Created on September 2, 2011, 1:55 PM
 */

#ifndef UTILITIES_MEMORY_DEBUGMEMORYTRACKER_H
#define	UTILITIES_MEMORY_DEBUGMEMORYTRACKER_H

#include "Utilities/Memory/Tracking/MemoryTracker.h"
#include <unordered_map>

namespace Utilities
{
    namespace Memory
    {

        class DebugMemoryTracker : public MemoryTracker
        {
        public:
             virtual MemoryDump getMemoryDump() const;
             
        protected:
            virtual void trackAllocation(const_byte_pointer ptr, size_t bytes, const std::type_info& type);
            virtual void trackDeallocation(const_byte_pointer ptr, size_t bytes, const std::type_info& type);
            
        private:
            typedef std::unordered_map<const_byte_pointer, AllocationInfo> AllocationMap;
            AllocationMap allocations;
        };
    }
}


#endif	/* UTILITIES_MEMORY_DEBUGMEMORYTRACKER_H */

