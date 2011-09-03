/* 
 * File:   Allocator.cpp
 * Author: madrenegade
 * 
 * Created on September 2, 2011, 10:49 PM
 */

#include <map>
#include <stdexcept>

#include "Utilities/Memory/Allocator.h"
#include "Utilities/Memory/constants.h"

#ifdef DEBUG
#include <glog/logging.h>
#include "Utilities/functions.h"
#endif

namespace Utilities
{
    namespace Memory
    {

        Allocator::Allocator(size_t maxSize, size_t pageSize, size_t blockSize)
        : memoryUsage(0), data(new char[maxSize]), maxSize(maxSize), pageSize(pageSize), blockSize(blockSize),
            pageCount(maxSize / pageSize)
        {
#ifdef DEBUG
            if (maxSize % pageSize != 0)
            {
                VLOG(1) << "Pool size: " << maxSize << std::endl
                    << "Page size: " << pageSize << std::endl
                    << "Rest: " << (maxSize % pageSize);
                
                throw std::invalid_argument("Pool size must be multiple of the page size");
            }
            
            if(pageSize % blockSize != 0)
            {
                VLOG(1) << "Page size: " << pageSize << std::endl
                    << "Block size: " << blockSize << std::endl
                    << "Rest: " << (pageSize % blockSize);
                
                throw std::invalid_argument("Page size must be multiple of the block size");
            }
            
            if(blockSize % 8 != 0)
            {
                VLOG(1) << "Block size: " << blockSize << std::endl
                    << "Rest: " << (blockSize % 8);
                
                throw std::invalid_argument("Block size must be multiple of the 8");
            }

            fillMemory(data.get(), maxSize, EMPTY);
#endif
        }

        bool Allocator::contains(const_pointer ptr) const
        {
            return allocations.find(ptr) != allocations.end();
        }

        size_t Allocator::getMemoryUsage() const
        {
            return memoryUsage;
        }

        double Allocator::getFragmentation() const
        {
            return getLargestFreeArea() / getFreeMemory();
        }

        void Allocator::registerPointer(const_pointer ptr, unsigned int page)
        {
            allocations[ptr] = page;
        }
        
        unsigned int Allocator::getBlocksPerPage() const
        {
            return pageSize / blockSize;
        }
    }
}
