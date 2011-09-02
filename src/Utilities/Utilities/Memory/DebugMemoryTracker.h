/* 
 * File:   DebugMemoryTracker.h
 * Author: madrenegade
 *
 * Created on September 2, 2011, 1:55 PM
 */

#ifndef UTILITIES_MEMORY_DEBUGMEMORYTRACKER_H
#define	UTILITIES_MEMORY_DEBUGMEMORYTRACKER_H

#include "Utilities/Memory/MemoryTracker.h"

namespace Utilities
{
    namespace Memory
    {

        class DebugMemoryTracker : public MemoryTracker
        {
        protected:
            virtual void trackAllocation(const_pointer ptr, size_t bytes, const std::type_info& type);
            virtual void trackDeallocation(const_pointer ptr, size_t bytes, const std::type_info& type);
            
            virtual MemoryDump getMemoryDump() const;
        };
    }
}


#endif	/* UTILITIES_MEMORY_DEBUGMEMORYTRACKER_H */

