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
#include <unordered_map>
#include <vector>

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
            
            unsigned int getPageIDFor(const_pointer ptr) const;
            
            unsigned int getBlocksPerPage() const;
            
            virtual size_t getLargestFreeArea() const = 0;
            virtual size_t getFreeMemory() const = 0;
            
            typedef boost::shared_array<char> Page;
            unsigned int requestNewPage();
            
            pointer getPage(unsigned int id) const;
            
            size_t memoryUsage;
            
            const size_t MAX_SIZE;
            const size_t PAGE_SIZE;
            const size_t BLOCK_SIZE;
            
            const unsigned int MAX_PAGE_COUNT;
            
            std::vector<Page> pages;
        };
    }
}

#endif	/* UTILITIES_MEMORY_ALLOCATOR_H */

