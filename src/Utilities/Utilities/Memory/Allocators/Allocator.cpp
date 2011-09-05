/* 
 * File:   Allocator.cpp
 * Author: madrenegade
 * 
 * Created on September 2, 2011, 10:49 PM
 */

#include <map>
#include <stdexcept>

#include "Utilities/Memory/Allocators/Allocator.h"
#include "Utilities/Memory/constants.h"
#include "Utilities/Memory/Exceptions/OutOfMemoryException.h"

#ifdef DEBUG
#include <glog/logging.h>
#include <glog/raw_logging.h>
#include "Utilities/functions.h"
#endif

namespace Utilities
{
    namespace Memory
    {

        Allocator::Allocator(size_t maxSize, size_t pageSize, size_t blockSize)
        : memoryUsage(0), MAX_SIZE(maxSize), PAGE_SIZE(pageSize), BLOCK_SIZE(blockSize),
            MAX_PAGE_COUNT(maxSize / pageSize)
        {
            pages.reserve(MAX_PAGE_COUNT);
                
#ifdef DEBUG
            if (maxSize % pageSize != 0)
            {
                RAW_VLOG(1, "Pool size: %i\nPage size: %i\nRest: %i", maxSize, pageSize, maxSize % pageSize);
                
                throw std::invalid_argument("Pool size must be multiple of the page size");
            }
            
            if(pageSize % blockSize != 0)
            {
                RAW_VLOG(1, "Page size: %i\nBlock size: %i\nRest: %i", pageSize, blockSize, pageSize % blockSize);
                
                throw std::invalid_argument("Page size must be multiple of the block size");
            }
            
            if(blockSize % BITS_PER_BYTE != 0)
            {
                RAW_VLOG(1, "Block size: %i\nRest: %i", blockSize, blockSize % BITS_PER_BYTE);
                
                throw std::invalid_argument("Block size must be multiple of BITS_PER_BYTE");
            }
#endif
        }

        bool Allocator::contains(const_pointer ptr) const
        {
            try
            {
                unsigned int page = getPageIDFor(ptr);
                
                return true;
            }
            catch(const std::logic_error& ex)
            {
                return false;
            }
        }

        size_t Allocator::getMemoryUsage() const
        {
            return memoryUsage;
        }

        double Allocator::getFragmentation() const
        {
            return 1.0 - getLargestFreeArea() / getFreeMemory();
        }
        
        unsigned int Allocator::getPageIDFor(const_pointer ptr) const
        {
            unsigned long lptr = reinterpret_cast<unsigned long>(ptr);
            
            for(unsigned int i = 0; i < pages.size(); ++i)
            {
                unsigned long pageStart = reinterpret_cast<unsigned long>(pages.at(i).get());
                
                unsigned long diff = lptr - pageStart;
                
                if(diff >= 0 && diff < PAGE_SIZE)
                {
                    return i;
                }
            }
            
            throw std::logic_error("Pointer not found in any page");
        }
        
        unsigned int Allocator::getBlocksPerPage() const
        {
            return PAGE_SIZE / BLOCK_SIZE;
        }
        
        pointer Allocator::requestNewPage()
        {
            if(pages.size() == MAX_PAGE_COUNT)
            {
                throw OutOfMemoryException("requestNewPage fail - amount of pages exceeded");
            }
            
            Page page(new byte[PAGE_SIZE]);
            pages.push_back(page);
            
            return page.get();
        }
        
        pointer Allocator::getPage(unsigned int id) const
        {
            return pages.at(id).get();
        }
    }
}
