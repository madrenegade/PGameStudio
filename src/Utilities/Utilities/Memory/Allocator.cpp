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
#endif

namespace Utilities
{
    namespace Memory
    {

        Allocator::Allocator(size_t maxSize, size_t pageSize, size_t blockSize)
        : memoryUsage(0), data(new char[maxSize]), maxSize(maxSize), pageSize(pageSize), blockSize(blockSize)
        {
#ifdef DEBUG
            if (maxSize % pageSize != 0)
            {
                VLOG(1) << "Pool size: " << maxSize << std::endl
                    << "Page size: " << pageSize << std::endl
                    << "Rest: " << (maxSize % pageSize);
                
                throw std::invalid_argument("Pool size must be multiple of the page size");
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

        void Allocator::fillMemory(pointer start, size_t bytes, char c)
        {
            for (size_t i = 0; i < bytes; ++i)
            {
                start[0] = c;
            }
        }

        unsigned int Allocator::getPageCount() const
        {
            return maxSize / pageSize;
        }
    }
}
