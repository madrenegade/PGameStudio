/* 
 * File:   Pool.h
 * Author: madrenegade
 *
 * Created on September 1, 2011, 4:27 PM
 */

#ifndef UTILITIES_MEMORY_POOL_H
#define	UTILITIES_MEMORY_POOL_H

#include <boost/scoped_array.hpp>

#include "Utilities/Memory/typedefs.h"

namespace Utilities
{
    namespace Memory
    {

        class Pool
        {
        public:
            virtual pointer allocate(size_t bytes) = 0;
            virtual void deallocate(const_pointer ptr, size_t sizeOfOneObject, size_t numObjects) = 0;
            
            virtual bool contains(const_pointer ptr) const = 0;
            
            size_t getFreeMemory() const;
            
        protected:
            Pool(size_t size);
            
            virtual size_t getMemoryUsage() const = 0;
            
            const size_t size;
        };
    }
}


#endif	/* UTILITIES_MEMORY_POOL_H */

