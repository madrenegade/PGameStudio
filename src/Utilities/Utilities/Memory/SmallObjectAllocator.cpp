/* 
 * File:   SmallObjectAllocator.cpp
 * Author: madrenegade
 * 
 * Created on September 2, 2011, 10:55 PM
 */

#include "Utilities/Memory/SmallObjectAllocator.h"
#include "Utilities/Memory/OutOfMemoryException.h"
#include "Utilities/functions.h"
#include "constants.h"

#include <glog/logging.h>
#include <bitset>
#include <cmath>
#include <list>
#include <stdexcept>

namespace Utilities
{
    namespace Memory
    {

        SmallObjectAllocator::SmallObjectAllocator(size_t maxSize, size_t pageSize, size_t blockSize)
        : Allocator(maxSize, pageSize, blockSize)
        {
            if((blockSize * 8) < (pageSize / blockSize))
            {
                throw std::logic_error("Blocksize too small for this page size");
            }
                
            freeBlocks.reserve(MAX_PAGE_COUNT);
        }

        pointer SmallObjectAllocator::allocate(size_t bytes)
        {
            pointer startOfPage;
            
            if (pagesWithFreeBlocks.empty())
            {
                startOfPage = requestNewPage();
                initializePage(startOfPage);
            }
            else
            {
                startOfPage = pagesWithFreeBlocks.front();
            }

            return allocateBlockIn(startOfPage);
        }

        pointer SmallObjectAllocator::allocateBlockIn(pointer startOfPage)
        {
            //VLOG(1) << "testing page " << page << " at offset " << pageOffset;

            int firstFreeBlock = findFreeBlockIn(startOfPage);

            if (firstFreeBlock != -1)
            {
                //VLOG(1) << "Using block " << firstFreeBlock << " in page " << page;

                pointer ptr = startOfPage + (BLOCK_SIZE * firstFreeBlock);

                markBlockAsUsed(firstFreeBlock, startOfPage);

                return ptr;
            }

            return 0;
        }

        void SmallObjectAllocator::deallocate(const_pointer ptr, size_t sizeOfOneObject, size_t numObjects)
        {
            const unsigned int page = getPageIDFor(ptr);

            pointer startOfPage = getPage(page);

            unsigned long diff = reinterpret_cast<unsigned long> (ptr) - reinterpret_cast<unsigned long> (startOfPage);

            markBlockAsFree(diff / BLOCK_SIZE, startOfPage);
        }

        size_t SmallObjectAllocator::getLargestFreeArea() const
        {
            
        }

        size_t SmallObjectAllocator::getFreeMemory() const
        {
            const size_t unusedPages = MAX_PAGE_COUNT - pages.size();

            size_t freeMemory = unusedPages * BLOCK_SIZE * (getUsableBlocksPerPage());

            for(FreeBlockMap::const_iterator i = freeBlocks.begin(); i != freeBlocks.end(); ++i)
            {
                freeMemory += i->second * BLOCK_SIZE;
            }

            return freeMemory;
        }

        void SmallObjectAllocator::initializePage(pointer page)
        {
            freeBlocks[page] = getUsableBlocksPerPage();
            pagesWithFreeBlocks.push_front(page);

            pointer tail = getTailFor(page);
            fillMemory(tail, BLOCK_SIZE, 255); // set all bits to 1
        }

//        pointer SmallObjectAllocator::getTailFor(unsigned int page) const
//        {
//            // offset of the last block (the allocation bitmask)
//            const size_t tailBlockOffset = BLOCK_SIZE * (getUsableBlocksPerPage());
//
//            return &getPage(page)[tailBlockOffset];
//        }
        
        pointer SmallObjectAllocator::getTailFor(pointer page) const
        {
            // offset of the last block (the allocation bitmask)
            const size_t tailBlockOffset = BLOCK_SIZE * (getUsableBlocksPerPage());

            return &page[tailBlockOffset];
        }

        int SmallObjectAllocator::findFreeBlockIn(pointer page) const
        {
            const size_t BLOCKS_PER_PAGE = getUsableBlocksPerPage();

            pointer tail = getTailFor(page);

            unsigned long* tailParts = reinterpret_cast<unsigned long*> (tail);

            // split tail block in parts of 8 bytes
            for (unsigned int i = 0; i < BLOCK_SIZE / sizeof (unsigned long); ++i)
            {
                int c = countZeroBitsFromRight(tailParts[i]);
                
                if(c == -1 || c > BLOCKS_PER_PAGE) continue;
                else return c;
            }
            
            return -1;
        }

        void SmallObjectAllocator::markBlockAsUsed(unsigned int block, pointer startOfPage)
        {
            freeBlocks[startOfPage] -= 1;

            if (freeBlocks[startOfPage] == 0)
            {
                pagesWithFreeBlocks.remove(startOfPage);
            }

            pointer tail = getTailFor(startOfPage);

            unsigned long* tailParts = reinterpret_cast<unsigned long*> (tail);

            unsigned long* tailPart = &tailParts[block / ULONG_BITS];

            // 1 << block creates a bitmask where the given block is 1 and the rest zero
            // with ~ this is negated so that all bits are one except the given block
            *tailPart &= ~(1 << block);
        }

        void SmallObjectAllocator::markBlockAsFree(unsigned int block, pointer startOfPage)
        {
            freeBlocks[startOfPage] += 1;

            if (freeBlocks[startOfPage] == 1)
            {
                pagesWithFreeBlocks.push_front(startOfPage);
            }

            pointer tail = getTailFor(startOfPage);

            unsigned long* tailParts = reinterpret_cast<unsigned long*> (tail);

            unsigned long* tailPart = &tailParts[block / ULONG_BITS];

            *tailPart |= (1 << block);
        }

        unsigned int SmallObjectAllocator::getUsableBlocksPerPage() const
        {
            return getBlocksPerPage() - 1;
        }
    }
}


