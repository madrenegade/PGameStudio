/* 
 * File:   MediumObjectAllocator.cpp
 * Author: madrenegade
 * 
 * Created on September 2, 2011, 10:59 PM
 */

#include "Utilities/Memory/Allocators/MediumObjectAllocator.h"
#include "Utilities/Memory/Pages/PageManager.h"
#include "Utilities/Memory/constants.h"
#include "Utilities/functions.h"
#include <stdexcept>

#include <limits>
#include <glog/logging.h>
#include <glog/raw_logging.h>
#include <bitset>

namespace Utilities
{
    namespace Memory
    {

        MediumObjectAllocator::MediumObjectAllocator(const boost::shared_ptr<PageManager>& pageManager, size_t blockSize)
        : Allocator(pageManager, blockSize), USABLE_BLOCKS_PER_PAGE(pageManager->getPageSize() / blockSize - 1)
        {
            // the tail block can handle this amount of blocks
            const size_t BLOCK_SIZE_IN_BITS = blockSize * BITS_PER_BYTE;

            // this amount of bits is needed to handle all blocks in the page except the tail block
            const size_t NEEDED_BITS_IN_TAIL_FOR_ALLOCATIONS = (pageManager->getPageSize() / blockSize) - 1;
            const size_t NEEDED_BITS_IN_TAIL_FOR_AMOUNT_OF_FREE_BLOCKS = sizeof (unsigned short) * BITS_PER_BYTE;

            const size_t NEEDED_BITS_IN_TAIL = NEEDED_BITS_IN_TAIL_FOR_ALLOCATIONS + NEEDED_BITS_IN_TAIL_FOR_AMOUNT_OF_FREE_BLOCKS;

            if (NEEDED_BITS_IN_TAIL_FOR_ALLOCATIONS > std::numeric_limits<unsigned short>::max())
            {
                throw std::logic_error("MOA: At most 65535 blocks are allowed (increase blocksize or decrease page size)");
            }

            if (BLOCK_SIZE_IN_BITS < NEEDED_BITS_IN_TAIL)
            {
                throw std::logic_error("MOA: Blocksize too small for this page size");
            }
        }

        pointer MediumObjectAllocator::allocate(size_t bytes)
        {
            pointer startOfPage = 0;

            if (pagesWithFreeBlocks.empty())
            {
                startOfPage = pageManager->requestNewPage();
                initializePage(startOfPage);
            }
            else
            {
                startOfPage = pagesWithFreeBlocks.front();
                
                // TODO: check that page has enough free blocks!!!
                // TODO: store amount of largest range of free blocks before amount of free blocks at the end
                // of the page
            }

            const size_t neededBlocks = std::ceil(static_cast<double> (bytes) / static_cast<double> (BLOCK_SIZE));

            return allocateBlocksIn(startOfPage, neededBlocks);
        }

        pointer MediumObjectAllocator::allocateBlocksIn(pointer startOfPage, size_t neededBlocks)
        {
            int startOfFreeBlocks = findFreeBlocksIn(startOfPage, neededBlocks);

            if (startOfFreeBlocks != -1)
            {
                markBlocksAsUsed(startOfFreeBlocks, startOfPage, neededBlocks);

                return startOfPage + (BLOCK_SIZE * startOfFreeBlocks);
            }

            return 0;
        }

        void MediumObjectAllocator::deallocate(const_pointer ptr, size_t sizeOfOneObject, size_t numObjects)
        {
            const pointer startOfPage = pageManager->getPageFor(ptr);

            size_t blocksToDeallocate = std::ceil(static_cast<double> (sizeOfOneObject * numObjects) / static_cast<double> (BLOCK_SIZE));

            markBlocksAsFree((ptr - startOfPage) / BLOCK_SIZE, startOfPage, blocksToDeallocate);
        }

        size_t MediumObjectAllocator::getFreeMemory() const
        {
            const size_t unusedPages = pageManager->getUnusedPages();

            size_t freeMemory = unusedPages * BLOCK_SIZE * USABLE_BLOCKS_PER_PAGE;

            for (unsigned int i = 0; i < pageManager->getPagesInUse(); ++i)
            {
                freeMemory += *getPointerToAmountOfFreeBlocksFor(pageManager->getPage(i)) * BLOCK_SIZE;
            }

            return freeMemory;
        }

        int MediumObjectAllocator::findFreeBlocksIn(pointer page, size_t neededBlocks) const
        {
            pointer tail = getTailFor(page);

            unsigned long* tailParts = reinterpret_cast<unsigned long*> (tail);

            unsigned long blockRangeBitmap = std::numeric_limits<unsigned long>().max();
            blockRangeBitmap >>= (ULONG_BITS - neededBlocks);

            const size_t possibleLeftShifts = ULONG_BITS - neededBlocks;

            // split tail block in parts of 8 bytes
            for (unsigned int i = 0; i < BLOCK_SIZE / sizeof (unsigned long); ++i)
            {
                unsigned long tailPart = tailParts[i];

                for (unsigned int j = 0; j <= possibleLeftShifts; ++j)
                {
                    unsigned long bitmap = blockRangeBitmap << j;

                    if ((tailPart & bitmap) == bitmap)
                    {
                        // here starts a range of free blocks
                        return (i * ULONG_BITS) + countZeroBitsFromRight(bitmap);
                    }
                }
            }

            return -1;
        }

        unsigned short* MediumObjectAllocator::getPointerToAmountOfFreeBlocksFor(pointer page) const
        {
            return reinterpret_cast<unsigned short*>(page + pageManager->getPageSize() - 2);
        }

        void MediumObjectAllocator::markBlocksAsUsed(unsigned int block, pointer startOfPage, size_t numBlocks)
        {
            unsigned short* amountOfFreeBlocks = getPointerToAmountOfFreeBlocksFor(startOfPage);

            *amountOfFreeBlocks -= numBlocks;

            if (*amountOfFreeBlocks == 0)
            {
                pagesWithFreeBlocks.remove(startOfPage);
            }

            pointer tail = getTailFor(startOfPage);

            unsigned long* tailParts = reinterpret_cast<unsigned long*> (tail);

            unsigned long* tailPart = &tailParts[block / ULONG_BITS];

            unsigned long x = ~(~0L << (block + numBlocks));
            x >>= block;
            x <<= block;

            *tailPart &= ~x;

            memoryUsage += numBlocks * BLOCK_SIZE;
        }

        void MediumObjectAllocator::markBlocksAsFree(unsigned int block, pointer startOfPage, size_t numBlocks)
        {
            unsigned short* amountOfFreeBlocks = getPointerToAmountOfFreeBlocksFor(startOfPage);

            *amountOfFreeBlocks += numBlocks;

            if (*amountOfFreeBlocks == 1)
            {
                pagesWithFreeBlocks.push_front(startOfPage);
            }

            unsigned long x = ~(~0L << (block + numBlocks));
            x >>= block;
            x <<= block;

            unsigned long* tailParts = reinterpret_cast<unsigned long*> (getTailFor(startOfPage));
            unsigned long* tailPart = &tailParts[block / ULONG_BITS];

            *tailPart |= x;

            memoryUsage -= BLOCK_SIZE * numBlocks;
        }

        void MediumObjectAllocator::initializePage(pointer page)
        {
            pagesWithFreeBlocks.push_front(page);

            pointer tail = getTailFor(page);

            // set all bits to 1
            fillMemory(tail, BLOCK_SIZE - 2, 0xFF);

            unsigned short* amountOfFreeBlocks = getPointerToAmountOfFreeBlocksFor(page);
            *amountOfFreeBlocks = USABLE_BLOCKS_PER_PAGE;
        }

        pointer MediumObjectAllocator::getTailFor(pointer page) const
        {
            return page + pageManager->getPageSize() - BLOCK_SIZE;
        }
    }
}