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
            
            virtual void deallocate(const_pointer ptr, size_t bytes) = 0;
            virtual void deallocateArray(const_pointer ptr, size_t bytes) = 0;
            
        protected:
            Pool(size_t size);
            
            const size_t size;
            
            boost::scoped_array<char> data;
        };
    }
}


#endif	/* UTILITIES_MEMORY_POOL_H */

