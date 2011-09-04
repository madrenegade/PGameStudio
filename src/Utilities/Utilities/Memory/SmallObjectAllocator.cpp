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

namespace Utilities
{
    namespace Memory
    {

        SmallObjectAllocator::SmallObjectAllocator(size_t maxSize, size_t pageSize, size_t blockSize)
        : Allocator(maxSize, pageSize, blockSize)
        {
            freeBlocks.reserve(maxPageCount);
        }

        pointer SmallObjectAllocator::allocate(size_t bytes)
        {
            if(pagesWithFreeBlocks.empty())
            {
                unsigned int page = requestNewPage();
                initializePage(page);
                
                pagesWithFreeBlocks[page] = 0;
            }
            
            unsigned page = pagesWithFreeBlocks.begin()->first;
            
            return allocateBlockIn(page);
        }

        pointer SmallObjectAllocator::allocateBlockIn(unsigned int page)
        {
            pointer startOfPage = getPage(page);

            //VLOG(1) << "testing page " << page << " at offset " << pageOffset;

            int firstFreeBlock = findFreeBlockIn(page);

            if (firstFreeBlock != -1)
            {
                //VLOG(1) << "Using block " << firstFreeBlock << " in page " << page;

                pointer ptr = startOfPage + (blockSize * firstFreeBlock);

//                registerPointer(ptr, page);
                markBlockAsUsed(firstFreeBlock, page);

                return ptr;
            }

            return 0;
        }

        void SmallObjectAllocator::deallocate(const_pointer ptr, size_t sizeOfOneObject, size_t numObjects)
        {
            unsigned int page = getPageIDFor(ptr);

            pointer startOfPage = getPage(page);

            unsigned long diff = reinterpret_cast<unsigned long> (ptr) - reinterpret_cast<unsigned long> (startOfPage);

            markBlockAsFree(diff / blockSize, page);
        }

        size_t SmallObjectAllocator::getLargestFreeArea() const
        {
            // TODO
            // go through all pages
        }

        size_t SmallObjectAllocator::getFreeMemory() const
        {
            // TODO
            // count all free blocks
        }

        void SmallObjectAllocator::initializePage(unsigned int page)
        {
            freeBlocks[page] = getBlocksPerPage();
            pagesWithFreeBlocks[page] = 0;

            pointer tail = getTailFor(page);
            fillMemory(tail, blockSize, 255); // set all bits to 1
        }

        pointer SmallObjectAllocator::getTailFor(unsigned int page) const
        {
            // offset of the last block (the allocation bitmask)
            const size_t tailBlockOffset = blockSize * (getBlocksPerPage() - 1);

            return &getPage(page)[tailBlockOffset];
        }

        int SmallObjectAllocator::findFreeBlockIn(unsigned int page) const
        {
            const size_t BLOCKS_PER_PAGE = getBlocksPerPage();

            pointer tail = getTailFor(page);

            unsigned long* tailParts = reinterpret_cast<unsigned long*> (tail);

            // split tail block in parts of 8 bytes
            for (unsigned int i = 0; i < blockSize / sizeof (unsigned long); ++i)
            {
                // shift one bit right at a time
                for (unsigned int j = 0; j < ULONG_BITS; ++j)
                {
                    const unsigned long blockNum = (ULONG_BITS * i) + j;

                    if (blockNum > BLOCKS_PER_PAGE - 1)
                    {
                        break;
                    }

                    if ((tailParts[i] >> (blockNum)) & 1)
                    {
                        // this bit is set so the block is free
                        //VLOG(1) << "Block " << (blockNum) << " is free";
                        return blockNum;
                    }
                }
            }

            return -1;
        }

        void SmallObjectAllocator::markBlockAsUsed(unsigned int block, unsigned int page)
        {
            freeBlocks[page] -= 1;

            if (freeBlocks[page] == 0)
            {
                pagesWithFreeBlocks.erase(page);
                //pagesWithFreeBlocks.remove(page);
            }

            pointer tail = getTailFor(page);

            unsigned long* tailParts = reinterpret_cast<unsigned long*> (tail);

            unsigned long* tailPart = &tailParts[block / ULONG_BITS];

            // 1 << block creates a bitmask where the given block is 1 and the rest zero
            // with ~ this is negated so that all bits are one except the given block
            *tailPart &= ~(1 << block);
        }

        void SmallObjectAllocator::markBlockAsFree(unsigned int block, unsigned int page)
        {
            freeBlocks[page] += 1;

            if (freeBlocks[page] == 1)
            {
                pagesWithFreeBlocks[page] = 1;
            }

            pointer tail = getTailFor(page);

            unsigned long* tailParts = reinterpret_cast<unsigned long*> (tail);

            unsigned long* tailPart = &tailParts[block / ULONG_BITS];

            *tailPart |= (1 << block);
        }
    }
}


