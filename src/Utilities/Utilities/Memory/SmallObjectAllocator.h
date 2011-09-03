/* 
 * File:   SmallObjectAllocator.h
 * Author: madrenegade
 *
 * Created on September 2, 2011, 10:55 PM
 */

#ifndef UTILITIES_MEMORY_SMALLOBJECTALLOCATOR_H
#define	UTILITIES_MEMORY_SMALLOBJECTALLOCATOR_H

#include "Utilities/Memory/Allocator.h"

#include <vector>
#include <list>
#include <unordered_set>

/**
 * The small object allocator uses fixed block sizes. At the end of each page
 * there is one block with a bitmask of allocated and free blocks.
 */

namespace Utilities
{
    namespace Memory
    {
        class SmallObjectAllocator : public Allocator
        {
        public:
            SmallObjectAllocator(size_t maxSize, size_t pageSize, size_t blockSize);
            
            virtual pointer allocate(size_t bytes);
            virtual void deallocate(const_pointer ptr, size_t sizeOfOneObject, size_t numObjects);

        protected:
            virtual size_t getLargestFreeArea() const;
            virtual size_t getFreeMemory() const;
            
        private:
            /**
             * Set each bit of the last block of each page to one.
             * This marks all blocks in the page as free.
             */
            void initializePageTails();
            
            /**
             * get the starting address of a page
             * @param page
             * @return the starting address of the given page
             */
            pointer getTailFor(unsigned int page) const;
            
            /**
             * find a free block using the page tail bitmask
             * @param page - the page to search for free blocks in
             * @return a block number or -1 if no block is free
             */
            int findFreeBlockIn(unsigned int page) const;
            
            void markBlockAsUsed(unsigned int block, unsigned int page);
            void markBlockAsFree(unsigned int block, unsigned int page);
            
            pointer allocateBlockIn(unsigned int page);
            
            // index is the page and value is the amount of free blocks
            std::vector<unsigned int> freeBlocks;
            
            // pair<page, freeBlocks>
            //std::list<unsigned int> pagesWithFreeBlocks;
            std::map<unsigned int, unsigned int> pagesWithFreeBlocks;
        };
    }
}


#endif	/* UTILITIES_MEMORY_SMALLOBJECTALLOCATOR_H */

