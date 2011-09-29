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
            SmallObjectAllocator(const boost::shared_ptr<PageManager>& pageManager, const size_t blockSize);
            
            virtual byte_pointer allocate(const size_t bytes);
            virtual void deallocate(const_byte_pointer ptr, const size_t sizeOfOneObject, const size_t numObjects);
            
            virtual size_t getFreeMemory() const;
            
        private:
            /**
             * Set each bit of the last block to one.
             * This marks all blocks in the page as free.
             */
            void initializePage(byte_pointer page);
            
            /**
             * get the starting address of a page tail
             * @param page
             * @return the starting address of the given page tail
             */
            byte_pointer getTailFor(byte_pointer page) const;
            
            unsigned short* getPointerToAmountOfFreeBlocksFor(byte_pointer page) const;
            
            /**
             * find a free block using the page tail bitmask
             * @param page - the page to search for free blocks in
             * @return a block number or -1 if no block is free
             */
            int findFreeBlockIn(byte_pointer page) const;
            
            void markBlockAsUsed(const unsigned int block, byte_pointer startOfPage);
            void markBlockAsFree(const unsigned int block, byte_pointer startOfPage);
            
            byte_pointer allocateBlockIn(byte_pointer startOfPage);
            
            const size_t USABLE_BLOCKS_PER_PAGE;
            std::list<byte_pointer> pagesWithFreeBlocks;
        };
    }
}


#endif	/* UTILITIES_MEMORY_SMALLOBJECTALLOCATOR_H */

