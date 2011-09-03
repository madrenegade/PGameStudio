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
#include <boost/scoped_array.hpp>

namespace Utilities
{
    namespace Memory
    {

        class Allocator
        {
        public:
            virtual pointer allocate(size_t bytes) = 0;
            virtual void deallocate(const_pointer ptr, size_t sizeOfOneObject, size_t numObjects) = 0;
            
            bool contains(const_pointer ptr) const;

            size_t getMemoryUsage() const;
            double getFragmentation() const;

        protected:
            Allocator(size_t maxSize, size_t pageSize, size_t blockSize);
            
            void registerPointer(const_pointer ptr, unsigned int page);
            
            unsigned int getBlocksPerPage() const;
            
            virtual size_t getLargestFreeArea() const = 0;
            virtual size_t getFreeMemory() const = 0;
            
            size_t memoryUsage;
            
            boost::scoped_array<char> data;
            
            const size_t maxSize;
            const size_t pageSize;
            const size_t blockSize;
            
            const unsigned int pageCount;
            
            typedef std::map<const_pointer, unsigned int> PageMap;
            PageMap allocations;
        };
    }
}

#endif	/* UTILITIES_MEMORY_ALLOCATOR_H */

