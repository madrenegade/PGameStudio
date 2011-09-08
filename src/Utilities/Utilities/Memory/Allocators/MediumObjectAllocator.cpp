/* 
 * File:   MediumObjectAllocator.cpp
 * Author: madrenegade
 * 
 * Created on September 2, 2011, 10:59 PM
 */

#include "Utilities/Memory/Allocators/MediumObjectAllocator.h"
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

        MediumObjectAllocator::MediumObjectAllocator(size_t maxSize, size_t pageSize, size_t blockSize)
        : Allocator(maxSize, pageSize, blockSize)
        {
            if ((blockSize * BITS_PER_BYTE) < (pageSize / blockSize))
            {
                throw std::logic_error("MOA: Blocksize too small for this page size");
            }

            freeBlocks.reserve(MAX_PAGE_COUNT);
        }

        pointer MediumObjectAllocator::allocate(size_t bytes)
        {
            pointer startOfPage = 0;
            
            if (pagesWithFreeBlocks.empty())
            {
                startOfPage = requestNewPage();
                initializePage(startOfPage);
            }
            else
            {
                startOfPage = pagesWithFreeBlocks.front();
            }

            const size_t neededBlocks = std::ceil(static_cast<double> (bytes) / static_cast<double> (BLOCK_SIZE));
            
            return allocateBlocksIn(startOfPage, neededBlocks);
        }

        void MediumObjectAllocator::deallocate(const_pointer ptr, size_t sizeOfOneObject, size_t numObjects)
        {
            const unsigned int page = getPageIDFor(ptr);

            pointer startOfPage = getPage(page);

            unsigned long diff = reinterpret_cast<unsigned long> (ptr) - reinterpret_cast<unsigned long> (startOfPage);
            
            size_t blocksToDeallocate = std::ceil(static_cast<double> (sizeOfOneObject * numObjects) / static_cast<double> (BLOCK_SIZE));

            markBlocksAsFree(diff / BLOCK_SIZE, startOfPage, blocksToDeallocate);
        }

        size_t MediumObjectAllocator::getLargestFreeArea() const
        {

        }

        size_t MediumObjectAllocator::getFreeMemory() const
        {

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

        int MediumObjectAllocator::findFreeBlocksIn(pointer page, size_t neededBlocks) const
        {
            const size_t BLOCKS_PER_PAGE = getUsableBlocksPerPage();

            pointer tail = getTailFor(page);

            unsigned long* tailParts = reinterpret_cast<unsigned long*> (tail);
            
            unsigned long blockRangeBitmap = std::numeric_limits<unsigned long>().max();
            blockRangeBitmap >>= (ULONG_BITS - neededBlocks);
            
            const size_t possibleLeftShifts = ULONG_BITS - neededBlocks;

            // split tail block in parts of 8 bytes
            for (unsigned int i = 0; i < BLOCK_SIZE / sizeof (unsigned long); ++i)
            {
                unsigned long tailPart = tailParts[i];
                
                for(unsigned int j = 0; j <= possibleLeftShifts; ++j)
                {
                    unsigned long bitmap = blockRangeBitmap << j;
                    
                    if((tailPart & bitmap) == bitmap)
                    {
                        // here starts a range of free blocks
                        return countZeroBitsFromRight(bitmap);
                    }
                }
            }

            return -1;
        }
        
        void MediumObjectAllocator::markBlocksAsUsed(unsigned int block, pointer startOfPage, size_t numBlocks)
        {
            freeBlocks[startOfPage] -= numBlocks;

            if (freeBlocks[startOfPage] == 0)
            {
                pagesWithFreeBlocks.remove(startOfPage);
            }

            pointer tail = getTailFor(startOfPage);

            unsigned long* tailParts = reinterpret_cast<unsigned long*> (tail);

            unsigned long* tailPart = &tailParts[block / ULONG_BITS];

            unsigned long x = ~(~0 << (block + numBlocks));
            x >>= block;
            x <<= block;

            *tailPart &= ~x;

            memoryUsage += numBlocks * BLOCK_SIZE;
        }
        
        void MediumObjectAllocator::markBlocksAsFree(unsigned int block, pointer startOfPage, size_t numBlocks)
        {
            freeBlocks[startOfPage] += numBlocks;

            if (freeBlocks[startOfPage] == numBlocks)
            {
                pagesWithFreeBlocks.push_front(startOfPage);
            }
            
            unsigned long x = ~(~0 << (block + numBlocks));
            x >>= block;
            x <<= block;

            unsigned long* tailParts = reinterpret_cast<unsigned long*> (getTailFor(startOfPage));
            unsigned long* tailPart = &tailParts[block / ULONG_BITS];

            *tailPart |= x;

            memoryUsage -= BLOCK_SIZE * numBlocks;
        }

        void MediumObjectAllocator::initializePage(pointer page)
        {
            RAW_LOG_INFO("initialize page");
            
            freeBlocks[page] = getUsableBlocksPerPage();
            pagesWithFreeBlocks.push_front(page);

            pointer tail = getTailFor(page);
            fillMemory(tail, BLOCK_SIZE, 0xFF); // set all bits to 1
        }

        unsigned int MediumObjectAllocator::getUsableBlocksPerPage() const
        {
            return getBlocksPerPage() - 1;
        }

        pointer MediumObjectAllocator::getTailFor(pointer page) const
        {
            // offset of the last but one block (the allocation bitmap)
            const size_t blockOffset = BLOCK_SIZE * (getUsableBlocksPerPage());

            return &page[blockOffset];
        }
    }
}