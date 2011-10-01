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
#include "Utilities/Memory/Exceptions/OutOfMemoryException.h"
#include <stdexcept>

#include <limits>
#include <glog/logging.h>
#include <glog/raw_logging.h>
#include <bitset>

#include <cmath>

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
            const size_t NEEDED_BITS_IN_TAIL_FOR_LARGEST_FREE_BLOCK_RANGE = sizeof (unsigned short) * BITS_PER_BYTE;

            const size_t NEEDED_BITS_IN_TAIL = NEEDED_BITS_IN_TAIL_FOR_ALLOCATIONS +
                                               NEEDED_BITS_IN_TAIL_FOR_LARGEST_FREE_BLOCK_RANGE +
                                               NEEDED_BITS_IN_TAIL_FOR_AMOUNT_OF_FREE_BLOCKS;

            if (NEEDED_BITS_IN_TAIL_FOR_ALLOCATIONS > std::numeric_limits<unsigned short>::max())
            {
                throw std::logic_error("MOA: At most 65535 blocks are allowed (increase blocksize or decrease page size)");
            }

            if (BLOCK_SIZE_IN_BITS < NEEDED_BITS_IN_TAIL)
            {
                throw std::logic_error("MOA: Blocksize too small for this page size");
            }
        }

        byte_pointer MediumObjectAllocator::allocate(size_t bytes)
        {
#ifdef DEBUG
            if(bytes > USABLE_BLOCKS_PER_PAGE * BLOCK_SIZE)
            {
                throw OutOfMemoryException("Cannot allocate more bytes than USABLE_BLOCKS_PER_PAGE * BLOCK_SIZE");
            }
#endif

            byte_pointer startOfPage = 0;

            if (pagesWithFreeBlocks.empty())
            {
                startOfPage = pageManager->requestNewPage();
                initializePage(startOfPage);
            }
            else
            {
                for (PagesWithFreeBlocksList::const_iterator i = pagesWithFreeBlocks.begin(); i != pagesWithFreeBlocks.end(); ++i)
                {
                    byte_pointer page = pagesWithFreeBlocks.front();

                    size_t largestBlockRange = *getPointerToLargestFreeBlockRangeFor(page) * BLOCK_SIZE;

                    if (largestBlockRange >= bytes)
                    {
                        startOfPage = page;
                        break;
                    }
                }

                if (startOfPage == 0)
                {
                    startOfPage = pageManager->requestNewPage();
                    initializePage(startOfPage);
                }
            }

            const size_t neededBlocks = std::ceil(static_cast<double> (bytes) / static_cast<double> (BLOCK_SIZE));

            RAW_VLOG(4, "Needing %li blocks for %li bytes with blockSize=%li\nUsing page: %p", neededBlocks, bytes, BLOCK_SIZE, reinterpret_cast<const void*>(startOfPage));
            return allocateBlocksIn(startOfPage, neededBlocks);
        }

        byte_pointer MediumObjectAllocator::allocateBlocksIn(byte_pointer startOfPage, const size_t neededBlocks)
        {
            const int startOfFreeBlocks = findFreeBlocksIn(startOfPage, neededBlocks);
            RAW_VLOG(4, "Range: %i to %li", startOfFreeBlocks, (startOfFreeBlocks+neededBlocks-1));

            if (startOfFreeBlocks != -1)
            {
                markBlocksAsUsed(startOfFreeBlocks, startOfPage, neededBlocks);

                return startOfPage + (BLOCK_SIZE * startOfFreeBlocks);
            }

            return 0;
        }

        void MediumObjectAllocator::deallocate(const_byte_pointer ptr, size_t sizeOfOneObject, size_t numObjects)
        {
            const byte_pointer startOfPage = pageManager->getPageFor(ptr);

            const size_t blocksToDeallocate = std::ceil(static_cast<double> (sizeOfOneObject * numObjects) / static_cast<double> (BLOCK_SIZE));

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

        int MediumObjectAllocator::findFreeBlocksIn(byte_pointer page, const size_t neededBlocks) const
        {
            byte_pointer tail = getTailFor(page);

            unsigned long* tailParts = reinterpret_cast<unsigned long*> (tail);
            unsigned long tailPart = 0;

            unsigned long currentFreeBits = 0;

            for (unsigned int i = 0; i < BLOCK_SIZE / sizeof (unsigned long); ++i)
            {
                tailPart = tailParts[i];

                unsigned int currentBitInPart = 0;

                while(currentBitInPart < ULONG_BITS)
                {
                    unsigned int zeroBits = countZeroBitsFromRight(tailPart);

                    if(zeroBits != 0)
                    {
                        currentFreeBits = 0;
                        tailPart >>= zeroBits;
                        currentBitInPart += zeroBits;
                    }

                    unsigned int oneBits = countOneBitsFromRight(tailPart);
                    currentFreeBits += oneBits;
                    currentBitInPart += oneBits;

                    if(currentFreeBits >= neededBlocks)
                    {
                        const int block = (i * ULONG_BITS) + currentBitInPart - currentFreeBits;
                        return block;
                    }

                    tailPart >>= oneBits;
                }
            }

            return -1;
        }

        unsigned short* MediumObjectAllocator::getPointerToAmountOfFreeBlocksFor(byte_pointer page) const
        {
            return reinterpret_cast<unsigned short*> (page + pageManager->getPageSize() - 2);
        }

        unsigned short* MediumObjectAllocator::getPointerToLargestFreeBlockRangeFor(byte_pointer page) const
        {
            return reinterpret_cast<unsigned short*> (page + pageManager->getPageSize() - 4);
        }

        void MediumObjectAllocator::markBlocksAsUsed(const unsigned int block, byte_pointer startOfPage, const size_t numBlocks)
        {
            unsigned short* amountOfFreeBlocks = getPointerToAmountOfFreeBlocksFor(startOfPage);

            *amountOfFreeBlocks -= numBlocks;

            if (*amountOfFreeBlocks == 0)
            {
                pagesWithFreeBlocks.remove(startOfPage);
            }

            byte_pointer tail = getTailFor(startOfPage);
            unsigned long* tailParts = reinterpret_cast<unsigned long*> (tail);
            unsigned int partNum = block / ULONG_BITS;

            size_t blocksLeft = numBlocks;
            size_t currentBlock = block;

            while(blocksLeft > 0)
            {
                unsigned long* tailPart = &tailParts[partNum];

                const unsigned long relativeBlock = currentBlock % ULONG_BITS;

                unsigned long x = ~(~0UL << (relativeBlock + numBlocks));

                if(relativeBlock + blocksLeft >= ULONG_BITS)
                {
                    blocksLeft -= (ULONG_BITS - relativeBlock);
                    currentBlock += ULONG_BITS - relativeBlock;
                    x = ~0UL;
                }
                else
                {
                    blocksLeft = 0;
                }

                x >>= relativeBlock;

                x <<= relativeBlock;

                *tailPart ^= x;

                ++partNum;
            }

            updateLargestBlockRangeFor(startOfPage);

            memoryUsage += numBlocks * BLOCK_SIZE;
        }

        void MediumObjectAllocator::markBlocksAsFree(unsigned int block, byte_pointer startOfPage, size_t numBlocks)
        {
            unsigned short* amountOfFreeBlocks = getPointerToAmountOfFreeBlocksFor(startOfPage);

            *amountOfFreeBlocks += numBlocks;

            if (*amountOfFreeBlocks == 1)
            {
                pagesWithFreeBlocks.push_front(startOfPage);
            }

            byte_pointer tail = getTailFor(startOfPage);
            unsigned long* tailParts = reinterpret_cast<unsigned long*> (tail);
            unsigned int partNum = block / ULONG_BITS;

            size_t blocksLeft = numBlocks;
            size_t currentBlock = block;

            while(blocksLeft > 0)
            {
                unsigned long* tailPart = &tailParts[partNum];

                const unsigned long relativeBlock = currentBlock % ULONG_BITS;

                unsigned long x = ~(~0UL << (relativeBlock + numBlocks));

                if(relativeBlock + blocksLeft >= ULONG_BITS)
                {
                    blocksLeft -= (ULONG_BITS - relativeBlock);
                    currentBlock += ULONG_BITS - relativeBlock;
                    x = ~0UL;
                }
                else
                {
                    blocksLeft = 0;
                }

                x >>= relativeBlock;

                x <<= relativeBlock;

                *tailPart |= x;

                ++partNum;
            }

//            unsigned short before = *getPointerToLargestFreeBlockRangeFor(startOfPage);
//            RAW_LOG_INFO("DEALLOC_BEFORE: %i", before);

            updateLargestBlockRangeFor(startOfPage);

//            unsigned short after = *getPointerToLargestFreeBlockRangeFor(startOfPage);
//            RAW_LOG_INFO("DEALLOC_AFTER: %i", after);

            memoryUsage -= BLOCK_SIZE * numBlocks;
        }

        void MediumObjectAllocator::initializePage(byte_pointer page)
        {
            pagesWithFreeBlocks.push_front(page);

            byte_pointer tail = getTailFor(page);

            // set all bits to 1
            const unsigned char ONE = 0xFF;
            fillMemory(tail, BLOCK_SIZE - 4, ONE);

            unsigned short* amountOfFreeBlocks = getPointerToAmountOfFreeBlocksFor(page);
            *amountOfFreeBlocks = USABLE_BLOCKS_PER_PAGE;

            unsigned short* freeBlockRange = getPointerToLargestFreeBlockRangeFor(page);
            *freeBlockRange = USABLE_BLOCKS_PER_PAGE;
        }

        byte_pointer MediumObjectAllocator::getTailFor(byte_pointer page) const
        {
            return page + pageManager->getPageSize() - BLOCK_SIZE;
        }

        void MediumObjectAllocator::updateLargestBlockRangeFor(byte_pointer page)
        {
            unsigned long* tailParts = reinterpret_cast<unsigned long*> (getTailFor(page));

            unsigned short* largestBlockRange = getPointerToLargestFreeBlockRangeFor(page);

            unsigned int totalShifts = 0;

            unsigned short currentMax = 0;
            unsigned short temp = 0;

            int zeroBits = 0;

            unsigned long tailPart = 0;
            unsigned int j = 0;

            for (unsigned int i = 0; i  < std::ceil(static_cast<double>(USABLE_BLOCKS_PER_PAGE) / static_cast<double>(ULONG_BITS)); ++i)
            {
                tailPart = tailParts[i];

                j = 0;

                while(totalShifts < USABLE_BLOCKS_PER_PAGE && j < ULONG_BITS)
                {
                    zeroBits = countZeroBitsFromRight(tailPart);

                    if(zeroBits == 0)
                    {
                        ++temp;
                    }

                    if(temp > currentMax)
                    {
                        currentMax = temp;
                    }

                    if(zeroBits > 0)
                    {
                        temp = 0;
                        tailPart >>= zeroBits;
                        totalShifts += zeroBits;
                        j += zeroBits;
                    }
                    else
                    {
                        tailPart >>= 1;
                        ++totalShifts;
                        ++j;
                    }
                }
            }

            *largestBlockRange = currentMax;
        }
    }
}
