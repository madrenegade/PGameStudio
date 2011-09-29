/*
 * File:   MediumObjectAllocator.h
 * Author: madrenegade
 *
 * Created on September 2, 2011, 10:59 PM
 */

#ifndef UTILITIES_MEMORY_MEDIUMOBJECTALLOCATOR_H
#define	UTILITIES_MEMORY_MEDIUMOBJECTALLOCATOR_H

#include "Utilities/Memory/Allocators/Allocator.h"

#include <unordered_map>
#include <list>

namespace Utilities
{
    namespace Memory
    {
        /**
         * This allocator is used for fast allocations of medium-sized objects. The memory
         * pages are separated into equally sized blocks. An allocation can span one
         * or more blocks.
         */
        class MediumObjectAllocator : public Allocator
        {
        public:
            MediumObjectAllocator(const boost::shared_ptr<PageManager>& pageManager, const size_t blockSize);

            virtual byte_pointer allocate(const size_t bytes);
            virtual void deallocate(const_byte_pointer ptr, const size_t sizeOfOneObject, const size_t numObjects);

            virtual size_t getFreeMemory() const;

        private:
            byte_pointer allocateBlocksIn(byte_pointer startOfPage, const size_t neededBlocks);
            int findFreeBlocksIn(byte_pointer page, const size_t neededBlocks) const;
            void markBlocksAsUsed(const unsigned int block, byte_pointer startOfPage, const size_t numBlocks);
            void markBlocksAsFree(const unsigned int block, byte_pointer startOfPage, const size_t numBlocks);

            /**
             * Set each bit of the last block to one. This marks all blocks in the page as free.
             * Set all blocks in the last but one block to zero.
             */
            void initializePage(byte_pointer page);

            byte_pointer getTailFor(byte_pointer page) const;

            unsigned short* getPointerToAmountOfFreeBlocksFor(byte_pointer page) const;
            unsigned short* getPointerToLargestFreeBlockRangeFor(byte_pointer page) const;

            void updateLargestBlockRangeFor(byte_pointer page);

            const size_t USABLE_BLOCKS_PER_PAGE;

            typedef std::list<byte_pointer> PagesWithFreeBlocksList;
            PagesWithFreeBlocksList pagesWithFreeBlocks;
        };
    }
}

#endif	/* UTILITIES_MEMORY_MEDIUMOBJECTALLOCATOR_H */

