/* 
 * File:   Allocator.h
 * Author: madrenegade
 *
 * Created on September 2, 2011, 10:49 PM
 */

#ifndef UTILITIES_MEMORY_ALLOCATOR_H
#define	UTILITIES_MEMORY_ALLOCATOR_H

#include "Utilities/Memory/typedefs.h"

#include <map>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <unordered_map>
#include <vector>

namespace Utilities
{
    namespace Memory
    {
        class PageManager;
        
        class Allocator
        {
        public:
            virtual byte_pointer allocate(const size_t bytes) = 0;
            virtual void deallocate(const_byte_pointer ptr, const size_t sizeOfOneObject, const size_t numObjects) = 0;
            
            bool contains(const_byte_pointer ptr) const;

            size_t getMemoryUsage() const;
            virtual size_t getFreeMemory() const = 0;

        protected:
            Allocator(const boost::shared_ptr<PageManager>& pageManager, const size_t blockSize);
            
            const boost::shared_ptr<PageManager> pageManager;
            
            size_t memoryUsage;
            
            const size_t BLOCK_SIZE;
        };
    }
}

#endif	/* UTILITIES_MEMORY_ALLOCATOR_H */

