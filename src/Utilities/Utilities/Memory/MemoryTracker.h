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
            
            template<typename T>
            void trackAllocation(const T* ptr, size_t bytes)
            {
                trackAllocation(reinterpret_cast<const_pointer>(ptr), bytes, typeid(T));
            }
            
            template<typename T>
            void trackDeallocation(const T* ptr, size_t bytes)
            {
                trackDeallocation(reinterpret_cast<const_pointer>(ptr), bytes, typeid(T));
            }
            
            void trackAllocation(const_pointer ptr, size_t bytes, const std::type_info& type);
            void trackDeallocation(const_pointer ptr, size_t bytes, const std::type_info& type);

            size_t getAllocatedMemorySize() const;

        private:
            void verifyUnused(const_pointer ptr) const;
            void verify(const_pointer ptr, size_t bytes, const std::type_info& type) const;
            
            bool isTracked(const_pointer ptr) const;
            
            void assertThatPointerIsTracked(const AllocationInfo& actual) const;
            void assertDetailsMatch(const AllocationInfo& expected, const AllocationInfo& actual) const;

            typedef std::map<const_pointer, AllocationInfo> BlockMap;
            BlockMap blocks;

            size_t memorySize;
		};
	}
}

#endif // UTILITIES_MEMORY_MEMORYTRACKER_H
