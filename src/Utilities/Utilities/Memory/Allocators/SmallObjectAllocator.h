/* 
 * File:   SmallObjectAllocator.h
 * Author: madrenegade
 *
 * Created on September 2, 2011, 10:55 PM
 */

#ifndef UTILITIES_MEMORY_SMALLOBJECTALLOCATOR_H
#define	UTILITIES_MEMORY_SMALLOBJECTALLOCATOR_H

#include "Utilities/Memory/Allocators/Allocator.h"

#include <vector>
#include <list>
#include <unordered_map>
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
            
            virtual size_t getFreeMemory() const;

        protected:
            virtual size_t getLargestFreeArea() const;
            
        private:
            /**
             * Set each bit of the last block the to one.
             * This marks all blocks in the page as free.
             */
            void initializePage(pointer page);
            
            /**
             * get the starting address of a page tail
             * @param page
             * @return the starting address of the given page tail
             */
            pointer getTailFor(pointer page) const;
            
            /**
             * find a free block using the page tail bitmask
             * @param page - the page to search for free blocks in
             * @return a block number or -1 if no block is free
             */
            int findFreeBlockIn(pointer page) const;
            
            void markBlockAsUsed(unsigned int block, pointer startOfPage);
            void markBlockAsFree(unsigned int block, pointer startOfPage);
            
            unsigned int getUsableBlocksPerPage() const;
            
            pointer allocateBlockIn(pointer startOfPage);
            
            // page start and amount of free blocks
            typedef std::unordered_map<pointer, unsigned int> FreeBlockMap;
            FreeBlockMap freeBlocks;
            
            std::list<pointer> pagesWithFreeBlocks;
        };
    }
}


#endif	/* UTILITIES_MEMORY_SMALLOBJECTALLOCATOR_H */

