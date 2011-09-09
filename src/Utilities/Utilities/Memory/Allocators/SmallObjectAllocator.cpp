/* 
 * File:   SmallObjectAllocator.cpp
 * Author: madrenegade
 * 
 * Created on September 2, 2011, 10:55 PM
 */

#include "Utilities/Memory/Allocators/SmallObjectAllocator.h"
#include "Utilities/Memory/Exceptions/OutOfMemoryException.h"
#include "Utilities/functions.h"
#include "Utilities/Memory/constants.h"

#include <glog/logging.h>
#include <glog/raw_logging.h>
#include <bitset>
#include <cmath>
#include <list>
#include <stdexcept>
#include <limits>

namespace Utilities
{
    namespace Memory
    {

        SmallObjectAllocator::SmallObjectAllocator(size_t maxSize, size_t pageSize, size_t blockSize)
        : Allocator(maxSize, pageSize, blockSize)
        {
            // the tail block can handle this amount of blocks
            const size_t BLOCK_SIZE_IN_BITS = blockSize * BITS_PER_BYTE;
            
            // this amount of bits is needed to handle all blocks in the page except the tail block
            const size_t NEEDED_BITS_IN_TAIL_FOR_ALLOCATIONS = (pageSize / blockSize) - 1;
            const size_t NEEDED_BITS_IN_TAIL_FOR_AMOUNT_OF_FREE_BLOCKS = sizeof(unsigned short) * BITS_PER_BYTE;
            
            const size_t NEEDED_BITS_IN_TAIL = NEEDED_BITS_IN_TAIL_FOR_ALLOCATIONS + NEEDED_BITS_IN_TAIL_FOR_AMOUNT_OF_FREE_BLOCKS;
            
            if(NEEDED_BITS_IN_TAIL_FOR_ALLOCATIONS > std::numeric_limits<unsigned short>::max())
            {
                throw std::logic_error("SOA: At most 65535 blocks are allowed (increase blocksize or decrease page size)");
            }
            
            if (BLOCK_SIZE_IN_BITS < NEEDED_BITS_IN_TAIL)
            {
                throw std::logic_error("SOA: Blocksize too small for this page size");
            }
        }

        pointer SmallObjectAllocator::allocate(size_t bytes)
        {
#ifdef DEBUG
            if (bytes > BLOCK_SIZE)
            {
                throw std::logic_error("Block size too small for requested amount of bytes");
            }
#endif

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
            int firstFreeBlock = findFreeBlockIn(startOfPage);

            if (firstFreeBlock != -1)
            {
                markBlockAsUsed(firstFreeBlock, startOfPage);
                
                return startOfPage + (BLOCK_SIZE * firstFreeBlock);
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
            unsigned int largestAmountOfFreeConsecutiveBlocks = 0;

//            for (FreeBlockMap::const_iterator i = freeBlocks.begin(); i != freeBlocks.end(); ++i)
//            {
//                unsigned int freeConsecutiveBlocks = 0;
//                unsigned int tempFreeConsecutiveBlocks = 0;
//
//                pointer tail = getTailFor(i->first);
//                unsigned long* tailParts = reinterpret_cast<unsigned long*> (tail);
//
//                bool lastBlockWasFree = false;
//
//                // split tail in parts of sizeof(ulong) bytes
//                for (unsigned int i = 0; i < BLOCK_SIZE / sizeof (unsigned long); ++i)
//                {
//                    unsigned long tailPart = tailParts[i];
//
//                    for (unsigned int bit = 0; bit < ULONG_BITS; ++bit)
//                    {
//                        const unsigned int blockNum = (ULONG_BITS * i) + bit;
//
//                        if (blockNum > getUsableBlocksPerPage())
//                        {
//                            break;
//                        }
//
//                        if ((tailPart >> blockNum) & 1)
//                        {
//                            ++tempFreeConsecutiveBlocks;
//                            
//                            if (tempFreeConsecutiveBlocks > freeConsecutiveBlocks)
//                            {
//                                freeConsecutiveBlocks = tempFreeConsecutiveBlocks;
//                            }
//                        }
//                        else
//                        {
//                            if (tempFreeConsecutiveBlocks > freeConsecutiveBlocks)
//                            {
//                                freeConsecutiveBlocks = tempFreeConsecutiveBlocks;
//                            }
//
//                            tempFreeConsecutiveBlocks = 0;
//                        }
//                        
//                        if (freeConsecutiveBlocks > largestAmountOfFreeConsecutiveBlocks)
//                        {
//                            largestAmountOfFreeConsecutiveBlocks = freeConsecutiveBlocks;
//                        }
//                    }
//                }
//            }

            return largestAmountOfFreeConsecutiveBlocks * BLOCK_SIZE;
        }

        size_t SmallObjectAllocator::getFreeMemory() const
        {
            const size_t unusedPages = MAX_PAGE_COUNT - pages.size();

//            size_t freeMemory = unusedPages * BLOCK_SIZE * (getUsableBlocksPerPage());
//
//            for (FreeBlockMap::const_iterator i = freeBlocks.begin(); i != freeBlocks.end(); ++i)
//            {
//                freeMemory += i->second * BLOCK_SIZE;
//            }

            return 0; //freeMemory;
        }

        void SmallObjectAllocator::initializePage(pointer page)
        {
            pagesWithFreeBlocks.push_front(page);

            pointer tail = getTailFor(page);
            
            // set all bits to 1
            fillMemory(tail, BLOCK_SIZE, 0xFF);
        }

        pointer SmallObjectAllocator::getTailFor(pointer page) const
        {
            return page + PAGE_SIZE - BLOCK_SIZE;
        }
        
        pointer SmallObjectAllocator::getPointerToAmountOfFreeBlocksFor(pointer page) const
        {
            return page + PAGE_SIZE - 2;
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

                if (c == -1 || c > BLOCKS_PER_PAGE) continue;
                else return c;
            }

            return -1;
        }

        void SmallObjectAllocator::markBlockAsUsed(unsigned int block, pointer startOfPage)
        {
            // fetch amount of free blocks
            unsigned short* amountOfFreeBlocks = reinterpret_cast<unsigned short*>(getPointerToAmountOfFreeBlocksFor(startOfPage));
            
            //RAW_VLOG(1, "markAsUsed: Free blocks: %i", *amountOfFreeBlocks);
            
            *amountOfFreeBlocks -= 1;
            
            if(*amountOfFreeBlocks == 0)
            {
                pagesWithFreeBlocks.remove(startOfPage);
            }

            pointer tail = getTailFor(startOfPage);

            unsigned long* tailParts = reinterpret_cast<unsigned long*> (tail);

            unsigned long* tailPart = &tailParts[block / ULONG_BITS];

            // 1 << block creates a bitmask where the given block is 1 and the rest zero
            // with ~ this is negated so that all bits are one except the given block
            *tailPart &= ~(1 << block);

            memoryUsage += BLOCK_SIZE;
        }

        void SmallObjectAllocator::markBlockAsFree(unsigned int block, pointer startOfPage)
        {
            unsigned short* amountOfFreeBlocks = reinterpret_cast<unsigned short*>(getPointerToAmountOfFreeBlocksFor(startOfPage));
            
            //RAW_VLOG(1, "markAsFree: Free blocks: %i", *amountOfFreeBlocks);
            
            *amountOfFreeBlocks += 1;
            
            if(*amountOfFreeBlocks == 1)
            {
                pagesWithFreeBlocks.push_front(startOfPage);
            }

            pointer tail = getTailFor(startOfPage);

            unsigned long* tailParts = reinterpret_cast<unsigned long*> (tail);

            unsigned long* tailPart = &tailParts[block / ULONG_BITS];

            *tailPart |= (1 << block);

            memoryUsage -= BLOCK_SIZE;
        }

        unsigned int SmallObjectAllocator::getUsableBlocksPerPage() const
        {
            return getBlocksPerPage() - 1;
        }
    }
}


