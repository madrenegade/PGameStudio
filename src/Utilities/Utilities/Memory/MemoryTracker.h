#ifndef UTILITIES_MEMORY_MEMORYTRACKER_H
#define UTILITIES_MEMORY_MEMORYTRACKER_H

#include <map>
#include "Utilities/Memory/AllocationInfo.h"

namespace Utilities
{
	namespace Memory
	{
		class MemoryTracker
		{
		public:
            MemoryTracker();
            ~MemoryTracker();
            
            void trackAllocation(void* ptr, size_t bytes, const std::type_info& type);
            void trackDeallocation(void* ptr, size_t bytes, const std::type_info& type);

            size_t getAllocatedMemorySize() const;

        private:
            void verifyUnused(void* ptr) const;
            void verify(void* ptr, size_t bytes, const std::type_info& type) const;
            
            bool isTracked(const void* ptr) const;
            
            void assertThatPointerIsTracked(const AllocationInfo& actual) const;
            void assertDetailsMatch(const AllocationInfo& expected, const AllocationInfo& actual) const;

            typedef std::map<const void*, AllocationInfo> BlockMap;
            BlockMap blocks;

            size_t memorySize;
		};
	}
}

#endif // UTILITIES_MEMORY_MEMORYTRACKER_H
