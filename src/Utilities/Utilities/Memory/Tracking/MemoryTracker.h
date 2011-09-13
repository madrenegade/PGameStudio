#ifndef UTILITIES_MEMORY_MEMORYTRACKER_H
#define UTILITIES_MEMORY_MEMORYTRACKER_H

#include <vector>
#include <boost/shared_ptr.hpp>
#include "Utilities/Memory/AllocationInfo.h"

namespace Utilities
{
	namespace Memory
	{
		class MemoryTracker
		{
		public:
            typedef boost::shared_ptr<MemoryTracker> Ptr;
            typedef std::vector<AllocationInfo> MemoryDump;
            
            virtual ~MemoryTracker();
            
            template<typename T>
            void trackAllocation(const T* ptr, size_t bytes)
            {
                trackAllocation(reinterpret_cast<const_byte_pointer>(ptr), bytes, typeid(T));
                memoryUsage += bytes;
            }
            
            template<typename T>
            void trackDeallocation(const T* ptr, size_t bytes)
            {
                trackDeallocation(reinterpret_cast<const_byte_pointer>(ptr), bytes, typeid(T));
                memoryUsage -= bytes;
            }

            size_t getMemoryUsage() const;
            
            void logMemoryLeaks() const;
            
            virtual MemoryDump getMemoryDump() const = 0;
            
            void printMemoryDump() const;
            
        protected:
            MemoryTracker();
            
            virtual void trackAllocation(const_byte_pointer ptr, size_t bytes, const std::type_info& type) = 0;
            virtual void trackDeallocation(const_byte_pointer ptr, size_t bytes, const std::type_info& type) = 0;
            
        private:
            size_t memoryUsage;
		};
	}
}

#endif // UTILITIES_MEMORY_MEMORYTRACKER_H
