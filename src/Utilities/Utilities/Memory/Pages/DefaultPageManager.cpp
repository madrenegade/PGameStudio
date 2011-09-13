/* 
 * File:   PageManager.cpp
 * Author: madrenegade
 * 
 * Created on September 10, 2011, 9:26 AM
 */

#include "Utilities/Memory/Pages/DefaultPageManager.h"
#include "Utilities/Memory/Allocators/LargeObjectAllocator.h"

#include <stdexcept>

namespace Utilities
{
    namespace Memory
    {

        DefaultPageManager::DefaultPageManager(size_t maxSize, size_t pageSize)
        : PageManager(maxSize, pageSize), pageCount(0), dirty(false), lastPageSearchResult(0)
        {
            pages.reserve(MAX_PAGE_COUNT);
        }

        size_t DefaultPageManager::getPagesInUse() const
        {
            return pages.size();
        }

        byte_pointer DefaultPageManager::getPageFor(const_byte_pointer ptr)
        {
            // normally only deallocate needes this method
            // chances are good that the last deallocation was in the same memory page
            // so we check that and may return immediatly
            if(lastPageSearchResult != 0 && ptr >= lastPageSearchResult && ptr < lastPageSearchResult + PAGE_SIZE)
            {
                return lastPageSearchResult;
            }
                
            if(dirty)
            {
                std::sort(pages.begin(), pages.end());
                dirty = false;
            }
            
            lastPageSearchResult = binaryPageSearch(ptr);
            
            return lastPageSearchResult;
        }
        
        byte_pointer DefaultPageManager::binaryPageSearch(const_byte_pointer ptr) const
        {
            int first = 0;
            int last = pageCount - 1;
            int mid = 0;
            
            while(first <= last)
            {
                mid = (first + last) / 2;
                
                if(ptr < pages[mid].get()) // pointer is before that page
                {
                    last = mid - 1;
                }
                else if(ptr > pages[mid].get() + PAGE_SIZE) // pointer is beyond that page
                {
                    first = mid + 1;
                }
                else
                {
                    return pages[mid].get();
                }
            }
            
            throw std::logic_error("Pointer not found in any page");
        }
        
        byte_pointer DefaultPageManager::getPage(size_t i) const
        {
            return pages[i].get();
        }

        byte_pointer DefaultPageManager::allocatePage()
        {
            Page page(new byte[PAGE_SIZE]);
            
            pages.push_back(page);
            
            dirty = true;

            ++pageCount;

            return page.get();
        }
    }
}


