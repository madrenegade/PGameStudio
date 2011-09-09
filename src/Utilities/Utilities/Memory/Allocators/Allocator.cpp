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

#include <glog/logging.h>
#include <glog/raw_logging.h>

namespace Utilities
{
    namespace Memory
    {

        Allocator::Allocator(size_t maxSize, size_t pageSize, size_t blockSize)
        : memoryUsage(0), MAX_SIZE(maxSize), PAGE_SIZE(pageSize), BLOCK_SIZE(blockSize),
            MAX_PAGE_COUNT(maxSize / pageSize), pageCount(0)
        {
            pages.reserve(MAX_PAGE_COUNT);
                
#ifdef DEBUG
            if (maxSize % pageSize != 0)
            {
                RAW_LOG_ERROR("Pool size: %i\nPage size: %i\nRest: %i", maxSize, pageSize, maxSize % pageSize);
                
                throw std::invalid_argument("Pool size must be multiple of the page size");
            }
            
            if(pageSize % blockSize != 0)
            {
                RAW_LOG_ERROR("Page size: %i\nBlock size: %i\nRest: %i", pageSize, blockSize, pageSize % blockSize);
                
                throw std::invalid_argument("Page size must be multiple of the block size");
            }
            
            if(blockSize % BITS_PER_BYTE != 0)
            {
                RAW_LOG_ERROR("Block size: %i\nRest: %i", blockSize, blockSize % BITS_PER_BYTE);
                
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
        
#ifdef GCC
//         TODO: probably only valid for 64 bit systems
        typedef long long di __attribute__ ((vector_size (1 * sizeof(long long))));
        
        union ptrVector {
            di v;
            unsigned long ptr;
        };
        
        union diffVector {
            di v;
            long diff;
        };
#endif
        
        unsigned int Allocator::getPageIDFor(const_pointer ptr) const
        {
#ifdef GCC
            union ptrVector pageStarts, ptrs;
            union diffVector results;
            
            ptrs.ptr = reinterpret_cast<const unsigned long>(ptr);
            
            
            for(unsigned int i = 0; i < pageCount; ++i)
            {
                pageStarts.ptr = reinterpret_cast<const unsigned long>(pages[i].get());
                
                results.v = __builtin_ia32_psubq(ptrs.v, pageStarts.v);
                
                if(results.diff >= 0 && results.diff < PAGE_SIZE)
                {
                    //RAW_LOG_INFO("Page: 0x%lx", pages[i].get());
//                    RAW_LOG_INFO("Ptr: %i", ptrs.ptr);
                    //RAW_LOG_INFO("first for bits: %x", ((ptrs.ptr >> 60) << 60));
                    return i;
                }
            }
#else
            pointer pageStart = 0;
            long diff = 0;
            
            for(unsigned int i = 0; i < pages.size(); ++i)
            {
                pageStart = pages[i].get();
                
                diff = ptr - pageStart;
                
                if(diff >= 0 && diff < PAGE_SIZE)
                {
                    return i;
                }
            }
#endif
            
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
            
            ++pageCount;
            
            //RAW_LOG_INFO("Page: %i - 0x%lx", pages.size(), page.get());
            
            return page.get();
        }
        
        pointer Allocator::getPage(unsigned int id) const
        {
            return pages.at(id).get();
        }
    }
}
