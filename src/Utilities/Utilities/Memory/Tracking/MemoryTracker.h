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
            
            virtual ~MemoryTracker();
            
            template<typename T>
            void trackAllocation(const T* ptr, size_t bytes)
            {
                trackAllocation(reinterpret_cast<const_pointer>(ptr), bytes, typeid(T));
                memoryUsage += bytes;
            }
            
            template<typename T>
            void trackDeallocation(const T* ptr, size_t bytes)
            {
                trackDeallocation(reinterpret_cast<const_pointer>(ptr), bytes, typeid(T));
                memoryUsage -= bytes;
            }

            size_t getMemoryUsage() const;
            
            void logMemoryLeaks() const;
            
            
        protected:
            MemoryTracker();
            
            virtual void trackAllocation(const_pointer ptr, size_t bytes, const std::type_info& type) = 0;
            virtual void trackDeallocation(const_pointer ptr, size_t bytes, const std::type_info& type) = 0;
            
            typedef std::vector<AllocationInfo> MemoryDump;
            virtual MemoryDump getMemoryDump() const = 0;

        private:
            size_t memoryUsage;
		};
	}
}

#endif // UTILITIES_MEMORY_MEMORYTRACKER_H
