/* 
 * File:   Pool.h
 * Author: madrenegade
 *
 * Created on September 1, 2011, 4:27 PM
 */

#ifndef UTILITIES_MEMORY_POOL_H
#define	UTILITIES_MEMORY_POOL_H

#include <boost/scoped_array.hpp>
#include <boost/shared_ptr.hpp>

#include "Utilities/Memory/typedefs.h"
#include "Utilities/Memory/MemoryPoolSettings.h"
#include "Utilities/Memory/Allocators/SmallObjectAllocator.h"
#include "Utilities/Memory/Allocators/MediumObjectAllocator.h"
#include "Utilities/Memory/Allocators/LargeObjectAllocator.h"

namespace Utilities
{
    namespace Memory
    {
        class Pool
        {
        public:
            typedef boost::shared_ptr<Pool> Ptr;
            
            static Ptr create(const MemoryPoolSettings& settings = MemoryPoolSettings());
            
            byte_pointer allocate(size_t bytes);
            void deallocate(const_byte_pointer ptr, size_t sizeOfOneObject, size_t numObjects);
            
            size_t getMemoryUsage() const;
            
            bool contains(const_byte_pointer ptr) const;
            
        private:
            Pool(const MemoryPoolSettings& settings);
            
            const MemoryPoolSettings settings;
            
            SmallObjectAllocator smallObjects;
            MediumObjectAllocator mediumObjects;
            LargeObjectAllocator largeObjects;
            
            Allocator* getAllocatorFor(size_t bytes);
        };
    }
}


#endif	/* UTILITIES_MEMORY_POOL_H */

