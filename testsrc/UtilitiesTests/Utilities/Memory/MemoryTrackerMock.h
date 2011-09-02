/* 
 * File:   MemoryTrackerMock.h
 * Author: madrenegade
 *
 * Created on September 2, 2011, 12:38 PM
 */

#ifndef UTILITIES_MEMORY_MEMORYTRACKERMOCK_H
#define UTILITIES_MEMORY_MEMORYTRACKERMOCK_H

#include "Utilities/Memory/MemoryTracker.h"

namespace Utilities
{
    namespace Memory
    {

        class MemoryTrackerMock : public MemoryTracker
        {
        public:
            virtual ~MemoryTrackerMock();
            
        protected:
            virtual void trackAllocation(const_pointer ptr, size_t bytes, const std::type_info& type);
            virtual void trackDeallocation(const_pointer ptr, size_t bytes, const std::type_info& type);
            virtual MemoryDump getMemoryDump() const;
        };
    }
}


#endif	/* UTILITIES_MEMORY_MEMORYTRACKERMOCK_H */

