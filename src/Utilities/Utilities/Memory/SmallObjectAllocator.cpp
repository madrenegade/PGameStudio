/* 
 * File:   SmallObjectAllocator.cpp
 * Author: madrenegade
 * 
 * Created on September 2, 2011, 10:55 PM
 */

#include "Utilities/Memory/SmallObjectAllocator.h"
#include "Utilities/Memory/OutOfMemoryException.h"
#include "Utilities/functions.h"

#include <glog/logging.h>
#include <bitset>
#include <cmath>

namespace Utilities
{
    namespace Memory
    {

        SmallObjectAllocator::SmallObjectAllocator(size_t maxSize, size_t pageSize, size_t blockSize)
        : Allocator(maxSize, pageSize, blockSize)
        {
            initializePageTails();
        }

        pointer SmallObjectAllocator::allocate(size_t bytes)
        {
            unsigned long poolStart = reinterpret_cast<unsigned long> (data.get());

            // all data must go in exactly one block so the first free block is searched
            for (unsigned int page = 0; page < getPageCount(); ++page)
            {
                pointer startOfPage = &data[page * pageSize];
                unsigned long pageOffset = reinterpret_cast<unsigned long> (startOfPage) - poolStart;

                VLOG(1) << "testing page " << page << " at offset " << pageOffset;

                int firstFreeBlock = findFreeBlockIn(page);
                
                if(firstFreeBlock != -1)
                {
                    VLOG(1) << "Using block " << firstFreeBlock << " in page " << page;
                    
                    pointer ptr = startOfPage + (blockSize * firstFreeBlock);
                    
                    registerPointer(ptr, page);
                    markBlockAsUsed(firstFreeBlock, page);
                    
                    return ptr;
                }
            }
            
            throw OutOfMemoryException();

        }

        void SmallObjectAllocator::deallocate(const_pointer ptr, size_t sizeOfOneObject, size_t numObjects)
        {
            unsigned int page = allocations[ptr];
            
            pointer startOfPage = &data[page * pageSize];
            
            unsigned long diff = reinterpret_cast<unsigned long>(ptr) - reinterpret_cast<unsigned long>(startOfPage);
            
            markBlockAsFree(diff / blockSize, page);
        }

        size_t SmallObjectAllocator::getLargestFreeArea() const
        {
            // go through all pages
        }

        size_t SmallObjectAllocator::getFreeMemory() const
        {
            // count all free blocks
        }

        void SmallObjectAllocator::initializePageTails()
        {
            for (unsigned int page = 0; page < getPageCount(); ++page)
            {
                pointer tail = getTailFor(page);
                fillMemory(tail, blockSize, 255); // all bits set to 1
            }
        }

        pointer SmallObjectAllocator::getTailFor(unsigned int page) const
        {
            // tail is the last block so it starts at page end - blockSize
            // or page start + blockSize * (blocksPerPage-1)´
            return &data[pageSize * page + blockSize * (getBlocksPerPage() - 1)];
        }

        int SmallObjectAllocator::findFreeBlockIn(unsigned int page) const
        {
            pointer tail = getTailFor(page);
            
            unsigned long* tailParts = reinterpret_cast<unsigned long*> (tail);

            // split tail block in parts of 64 bits
            for (unsigned int i = 0; i < blockSize / sizeof (unsigned long); ++i)
            {
                // shift one bit right at a time
                for (int j = 0; j < 8 * sizeof (unsigned long); ++j)
                {
                    unsigned long blockNum = (64 * i) + j;

                    if (blockNum > getBlocksPerPage() - 1)
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
            pointer tail = getTailFor(page);
            
            unsigned long* tailParts = reinterpret_cast<unsigned long*> (tail);
            
            unsigned long* tailPart = &tailParts[block / 64];
            
            *tailPart &= ~(1 << block);
        }
        
        void SmallObjectAllocator::markBlockAsFree(unsigned int block, unsigned int page)
        {
            pointer tail = getTailFor(page);
            
            unsigned long* tailParts = reinterpret_cast<unsigned long*> (tail);
            
            unsigned long* tailPart = &tailParts[block / 64];
            
            *tailPart |= (1 << block);
        }
    }
}


