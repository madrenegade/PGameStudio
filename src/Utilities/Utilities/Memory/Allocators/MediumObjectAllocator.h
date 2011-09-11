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

        class MediumObjectAllocator : public Allocator
        {
        public:
            MediumObjectAllocator(const boost::shared_ptr<PageManager>& pageManager, size_t blockSize);
            
            virtual pointer allocate(size_t bytes);
            virtual void deallocate(const_pointer ptr, size_t sizeOfOneObject, size_t numObjects);

            virtual size_t getFreeMemory() const;
            
        private:
            pointer allocateBlocksIn(pointer startOfPage, size_t neededBlocks);
            int findFreeBlocksIn(pointer page, size_t neededBlocks) const;
            void markBlocksAsUsed(unsigned int block, pointer startOfPage, size_t numBlocks);
            void markBlocksAsFree(unsigned int block, pointer startOfPage, size_t numBlocks);
            
            /**
             * Set each bit of the last block to one. This marks all blocks in the page as free.
             * Set all blocks in the last but one block to zero.
             */
            void initializePage(pointer page);

            pointer getTailFor(pointer page) const;
            
            unsigned short* getPointerToAmountOfFreeBlocksFor(pointer page) const;
            unsigned short* getPointerToLargestFreeBlockRangeFor(pointer page) const;
            
            void updateLargestBlockRangeFor(pointer page);
            
            const size_t USABLE_BLOCKS_PER_PAGE;
            
            typedef std::list<pointer> PagesWithFreeBlocksList;
            PagesWithFreeBlocksList pagesWithFreeBlocks;
        };
    }
}

#endif	/* UTILITIES_MEMORY_MEDIUMOBJECTALLOCATOR_H */

