#ifndef UTILITIES_MEMORY_ABSTRACTMANAGER_H
#define UTILITIES_MEMORY_ABSTRACTMANAGER_H

#include <typeinfo>
#include "Utilities/Memory/MemoryTracker.h"

namespace Utilities
{
	namespace Memory
	{
		class AbstractMemoryManager
		{
		public:
			virtual ~AbstractMemoryManager();

			template<typename T>
			T* allocate(size_t n)
			{
			    const size_t BYTES_TO_ALLOCATE = n * sizeof(T);

			    #ifdef DEBUG
			    void* ptr = allocate(BYTES_TO_ALLOCATE, PREALLOCATION_BYTE);
			    #else
			    void* ptr = allocate(BYTES_TO_ALLOCATE, 0);
			    #endif

			    memoryTracker.trackAllocation(ptr, BYTES_TO_ALLOCATE, typeid(T));

                return reinterpret_cast<T*>(ptr);
			}

			template<typename T>
			void deallocate(T* ptr, size_t n)
			{
			    const size_t BYTES_TO_DEALLOCATE = n * sizeof(T);

			    deallocate(reinterpret_cast<void*>(ptr), BYTES_TO_DEALLOCATE);

			    memoryTracker.trackDeallocation(ptr, BYTES_TO_DEALLOCATE, typeid(T));
			}

		protected:
			AbstractMemoryManager();

			// allocate n bytes
			virtual void* allocate(size_t n, unsigned char prealloc) = 0;

			// deallocate n bytes
			virtual void deallocate(void* ptr, size_t n) = 0;

        private:
            static const unsigned char PREALLOCATION_BYTE = 'a';

            MemoryTracker memoryTracker;
		};
	}
}

#endif // UTILITIES_MEMORY_ABSTRACTMANAGER_H
