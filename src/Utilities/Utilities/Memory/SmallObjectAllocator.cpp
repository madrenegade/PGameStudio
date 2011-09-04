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
            freeBlocks.reserve(MAX_PAGE_COUNT);
        }

        pointer SmallObjectAllocator::allocate(size_t bytes)
        {
            if (pagesWithFreeBlocks.empty())
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

                pointer ptr = startOfPage + (BLOCK_SIZE * firstFreeBlock);

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

            markBlockAsFree(diff / BLOCK_SIZE, page);
        }

        size_t SmallObjectAllocator::getLargestFreeArea() const
        {
        }

        size_t SmallObjectAllocator::getFreeMemory() const
        {
            const size_t unusedPages = MAX_PAGE_COUNT - pages.size();

            size_t freeMemory = unusedPages * BLOCK_SIZE * (getUsableBlocksPerPage());

            for (unsigned int i = 0; i < freeBlocks.size(); ++i)
            {
                freeMemory += freeBlocks.at(i) * BLOCK_SIZE;
            }

            return freeMemory;
        }

        void SmallObjectAllocator::initializePage(unsigned int page)
        {
            freeBlocks[page] = getUsableBlocksPerPage();
            pagesWithFreeBlocks[page] = getUsableBlocksPerPage();

            pointer tail = getTailFor(page);
            fillMemory(tail, BLOCK_SIZE, 255); // set all bits to 1
        }

        pointer SmallObjectAllocator::getTailFor(unsigned int page) const
        {
            // offset of the last block (the allocation bitmask)
            const size_t tailBlockOffset = BLOCK_SIZE * (getUsableBlocksPerPage());

            return &getPage(page)[tailBlockOffset];
        }

        int countZeroBitsFromRight(unsigned long v)
        {
            int c = 0;

            if (v)
            {
                v = (v ^ (v - 1)) >> 1; // Set v's trailing 0s to 1s and zero rest
                for (c = 0; v; c++)
                {
                    v >>= 1;
                }
            }
            else
            {
                c = -1;
            }
            
            return c;
        }
        
        int countZeroBitsFromRight2(unsigned long v)
        {
            unsigned int c = ULONG_BITS;
            
            v &= -static_cast<long>(v);
            if(v) c--;
            if (v & 0xFFFFFFFF) c -= 32;
            if (v & 0x0000FFFF) c -= 16;
            if (v & 0x00FF00FF) c -= 8;
            if (v & 0x0F0F0F0F) c -= 4;
            if (v & 0x33333333) c -= 2;
            if (v & 0x55555555) c -= 1;
            
            return c;
        }

        int SmallObjectAllocator::findFreeBlockIn(unsigned int page) const
        {
            const size_t BLOCKS_PER_PAGE = getUsableBlocksPerPage();

            pointer tail = getTailFor(page);

            unsigned long* tailParts = reinterpret_cast<unsigned long*> (tail);

            // split tail block in parts of 8 bytes
            for (unsigned int i = 0; i < BLOCK_SIZE / sizeof (unsigned long); ++i)
            {
                int c = countZeroBitsFromRight2(tailParts[i]);
                
                if(c == -1 || c > BLOCKS_PER_PAGE) continue;
                else return c;
                
                // shift one bit right at a time
//                for (unsigned int j = 0; j < ULONG_BITS; ++j)
//                {
//                    const unsigned long blockNum = (ULONG_BITS * i) + j;
//
//                    if (blockNum > BLOCKS_PER_PAGE)
//                    {
//                        break;
//                    }
//
//                    if ((tailParts[i] >> (blockNum)) & 1)
//                    {
//                        // this bit is set so the block is free
//                        return blockNum;
//                    }
//                }
            }
            
            return -1;
        }

        void SmallObjectAllocator::markBlockAsUsed(unsigned int block, unsigned int page)
        {
            freeBlocks[page] -= 1;

            if (freeBlocks[page] == 0)
            {
                pagesWithFreeBlocks.erase(page);
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

        unsigned int SmallObjectAllocator::getUsableBlocksPerPage() const
        {
            return getBlocksPerPage() - 1;
        }
    }
}


