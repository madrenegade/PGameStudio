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
        : Allocator(pageManager, blockSize), USABLE_BLOCKS_PER_PAGE(pageManager->getPageSize() / blockSize - 1)
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

        byte_pointer SmallObjectAllocator::allocate(size_t bytes)
        {
#ifdef DEBUG
            if (bytes > BLOCK_SIZE)
            {
                throw std::logic_error("Block size too small for requested amount of bytes");
            }
#endif

            byte_pointer startOfPage;

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

        byte_pointer SmallObjectAllocator::allocateBlockIn(byte_pointer startOfPage)
        {
            int firstFreeBlock = findFreeBlockIn(startOfPage);

            if (firstFreeBlock != -1)
            {
                markBlockAsUsed(firstFreeBlock, startOfPage);
                
                return startOfPage + (BLOCK_SIZE * firstFreeBlock);
            }

            return 0;
        }

        void SmallObjectAllocator::deallocate(const_byte_pointer ptr, size_t sizeOfOneObject, size_t numObjects)
        {
            const byte_pointer startOfPage = pageManager->getPageFor(ptr);

            markBlockAsFree((ptr - startOfPage) / BLOCK_SIZE, startOfPage);
        }

        size_t SmallObjectAllocator::getFreeMemory() const
        {
            const size_t unusedPages = pageManager->getUnusedPages();

            size_t freeMemory = unusedPages * BLOCK_SIZE * USABLE_BLOCKS_PER_PAGE;

            for(unsigned int i = 0; i < pageManager->getPagesInUse(); ++i)
            {
                freeMemory += *getPointerToAmountOfFreeBlocksFor(pageManager->getPage(i)) * BLOCK_SIZE;
            }

            return freeMemory;
        }

        void SmallObjectAllocator::initializePage(byte_pointer page)
        {
            pagesWithFreeBlocks.push_front(page);

            byte_pointer tail = getTailFor(page);
            
            fillMemory(tail, BLOCK_SIZE - 2, 0xFF);
            
            unsigned short* amountOfFreeBlocks = getPointerToAmountOfFreeBlocksFor(page);
            *amountOfFreeBlocks = USABLE_BLOCKS_PER_PAGE;
        }

        byte_pointer SmallObjectAllocator::getTailFor(byte_pointer page) const
        {
            return page + pageManager->getPageSize() - BLOCK_SIZE;
        }
        
        unsigned short* SmallObjectAllocator::getPointerToAmountOfFreeBlocksFor(byte_pointer page) const
        {
            return reinterpret_cast<unsigned short*>(page + pageManager->getPageSize() - 2);
        }

        int SmallObjectAllocator::findFreeBlockIn(byte_pointer page) const
        {
            byte_pointer tail = getTailFor(page);

            unsigned long* tailParts = reinterpret_cast<unsigned long*> (tail);
            
            int realBlock = 0;

            // split tail block in parts of 8 bytes
            for (unsigned int i = 0; i < BLOCK_SIZE / sizeof (unsigned long); ++i)
            {
                int c = countZeroBitsFromRight(tailParts[i]);
                
                realBlock = (i * ULONG_BITS) + c;
                
                if (realBlock > USABLE_BLOCKS_PER_PAGE || c == ULONG_BITS) continue;
                else return realBlock;
            }

            return -1;
        }

        void SmallObjectAllocator::markBlockAsUsed(unsigned int block, byte_pointer startOfPage)
        {
            // fetch amount of free blocks
            unsigned short* amountOfFreeBlocks = getPointerToAmountOfFreeBlocksFor(startOfPage);
            
            *amountOfFreeBlocks -= 1;
            
            if(*amountOfFreeBlocks == 0)
            {
                pagesWithFreeBlocks.remove(startOfPage);
            }

            byte_pointer tail = getTailFor(startOfPage);

            unsigned long* tailParts = reinterpret_cast<unsigned long*> (tail);

            unsigned long* tailPart = &tailParts[block / ULONG_BITS];
            
            // 1 << block creates a bitmask where the given block is 1 and the rest zero
            // with ~ this is negated so that all bits are one except the given block
            *tailPart ^= (1L << (block % ULONG_BITS));

            memoryUsage += BLOCK_SIZE;
        }

        void SmallObjectAllocator::markBlockAsFree(unsigned int block, byte_pointer startOfPage)
        {
            unsigned short* amountOfFreeBlocks = getPointerToAmountOfFreeBlocksFor(startOfPage);
            
            *amountOfFreeBlocks += 1;
            
            if(*amountOfFreeBlocks == 1)
            {
                pagesWithFreeBlocks.push_front(startOfPage);
            }

            byte_pointer tail = getTailFor(startOfPage);

            unsigned long* tailParts = reinterpret_cast<unsigned long*> (tail);

            unsigned long* tailPart = &tailParts[block / ULONG_BITS];

            *tailPart |= (1L << (block % ULONG_BITS));

            memoryUsage -= BLOCK_SIZE;
        }
    }
}


