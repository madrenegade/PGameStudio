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
#include "Utilities/Memory/Pages/PageManager.h"

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

        SmallObjectAllocator::SmallObjectAllocator(const boost::shared_ptr<PageManager>& pageManager, size_t blockSize)
        : Allocator(pageManager, blockSize)
        {
            // the tail block can handle this amount of blocks
            const size_t BLOCK_SIZE_IN_BITS = blockSize * BITS_PER_BYTE;
            
            // this amount of bits is needed to handle all blocks in the page except the tail block
            const size_t NEEDED_BITS_IN_TAIL_FOR_ALLOCATIONS = (pageManager->getPageSize() / blockSize) - 1;
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
                startOfPage = pageManager->requestNewPage();
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
            
//            RAW_LOG_INFO("First free block: %i", firstFreeBlock);

            if (firstFreeBlock != -1)
            {
                markBlockAsUsed(firstFreeBlock, startOfPage);
                
                return startOfPage + (BLOCK_SIZE * firstFreeBlock);
            }

            return 0;
        }

        void SmallObjectAllocator::deallocate(const_pointer ptr, size_t sizeOfOneObject, size_t numObjects)
        {
            const pointer startOfPage = pageManager->getPageFor(ptr);

            markBlockAsFree((ptr - startOfPage) / BLOCK_SIZE, startOfPage);
        }

        size_t SmallObjectAllocator::getLargestFreeArea() const
        {
            unsigned int largestAmountOfFreeConsecutiveBlocks = 0;

            return largestAmountOfFreeConsecutiveBlocks * BLOCK_SIZE;
        }

        size_t SmallObjectAllocator::getFreeMemory() const
        {
            const size_t unusedPages = pageManager->getUnusedPages();

            size_t freeMemory = unusedPages * BLOCK_SIZE * (getUsableBlocksPerPage());

            for(unsigned int i = 0; i < pageManager->getPagesInUse(); ++i)
            {
                freeMemory += *reinterpret_cast<unsigned short*>(getPointerToAmountOfFreeBlocksFor(pageManager->getPage(i))) * BLOCK_SIZE;
            }

            return freeMemory;
        }

        void SmallObjectAllocator::initializePage(pointer page)
        {
            pagesWithFreeBlocks.push_front(page);

            pointer tail = getTailFor(page);
            
            // set all bits to 1
            fillMemory(tail, BLOCK_SIZE - 2, 0xFF);
            
            unsigned short* amountOfFreeBlocks = reinterpret_cast<unsigned short*>(getPointerToAmountOfFreeBlocksFor(page));
            *amountOfFreeBlocks = getUsableBlocksPerPage();
        }

        pointer SmallObjectAllocator::getTailFor(pointer page) const
        {
            return page + pageManager->getPageSize() - BLOCK_SIZE;
        }
        
        pointer SmallObjectAllocator::getPointerToAmountOfFreeBlocksFor(pointer page) const
        {
            return page + pageManager->getPageSize() - 2;
        }

        int SmallObjectAllocator::findFreeBlockIn(pointer page) const
        {
            const size_t BLOCKS_PER_PAGE = getUsableBlocksPerPage();

            pointer tail = getTailFor(page);

            unsigned long* tailParts = reinterpret_cast<unsigned long*> (tail);
            
            int realBlock = 0;

            // split tail block in parts of 8 bytes
            for (unsigned int i = 0; i < BLOCK_SIZE / sizeof (unsigned long); ++i)
            {
                int c = countZeroBitsFromRight(tailParts[i]);
//                std::bitset<ULONG_BITS> bitset(tailParts[i]);
//                RAW_LOG_INFO("i: %i", i);
//                RAW_LOG_INFO("PartBits: %s", bitset.to_string().c_str());
//                RAW_LOG_INFO("C: %i", c);
                realBlock = (i * ULONG_BITS) + c;
                
                if (realBlock > BLOCKS_PER_PAGE || c == ULONG_BITS) continue;
                else {
//                    RAW_LOG_INFO("Part: %i", i);
                    return realBlock;
                }
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
            
//            RAW_LOG_INFO("Mod part %i", (block / ULONG_BITS));
//            
//            std::bitset<ULONG_BITS> bitset(*tailParts);
//            RAW_LOG_INFO("before: %s", bitset.to_string().c_str());

            // 1 << block creates a bitmask where the given block is 1 and the rest zero
            // with ~ this is negated so that all bits are one except the given block
            *tailPart &= ~(1L << block);
            
//            std::bitset<ULONG_BITS> bitset2(*tailParts);
//            RAW_LOG_INFO("after: %s", bitset2.to_string().c_str());

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

            *tailPart |= (1L << block);

            memoryUsage -= BLOCK_SIZE;
        }

        unsigned short SmallObjectAllocator::getUsableBlocksPerPage() const
        {
            return getBlocksPerPage() - 1;
        }
    }
}


