/* 
 * File:   PageManager.cpp
 * Author: madrenegade
 * 
 * Created on September 10, 2011, 9:26 AM
 */

#include "Utilities/Memory/Pages/DefaultPageManager.h"

#include <stdexcept>

namespace Utilities
{
    namespace Memory
    {

        DefaultPageManager::DefaultPageManager(size_t maxSize, size_t pageSize)
        : PageManager(maxSize, pageSize), pageCount(0)
        {
            pages.reserve(MAX_PAGE_COUNT);
        }

        size_t DefaultPageManager::getPagesInUse() const
        {
            return pages.size();
        }

#ifdef GCC
        //         TODO: probably only valid for 64 bit systems
        typedef long long di __attribute__((vector_size(1 * sizeof (long long))));

        union ptrVector
        {
            di v;
            unsigned long ptr;
        };

        union diffVector
        {
            di v;
            long diff;
        };
#endif

        pointer DefaultPageManager::getPageFor(const_pointer ptr) const
        {
#ifdef GCC
            union ptrVector pageStarts, ptrs;
            union diffVector results;

            ptrs.ptr = reinterpret_cast<const unsigned long> (ptr);


            for (unsigned int i = 0; i < pageCount; ++i)
            {
                pageStarts.ptr = reinterpret_cast<const unsigned long> (pages[i].get());

                results.v = __builtin_ia32_psubq(ptrs.v, pageStarts.v);

                if (results.diff >= 0 && results.diff < PAGE_SIZE)
                {
                    //RAW_LOG_INFO("Page: 0x%lx", pages[i].get());
                    //                    RAW_LOG_INFO("Ptr: %i", ptrs.ptr);
                    //RAW_LOG_INFO("first for bits: %x", ((ptrs.ptr >> 60) << 60));
                    return getPage(i);
                }
            }
#else
            pointer pageStart = 0;
            long diff = 0;

            for (unsigned int i = 0; i < pages.size(); ++i)
            {
                pageStart = pages[i].get();

                diff = ptr - pageStart;

                if (diff >= 0 && diff < PAGE_SIZE)
                {
                    return i;
                }
            }
#endif

            throw std::logic_error("Pointer not found in any page");
        }
        
        pointer DefaultPageManager::getPage(size_t i) const
        {
            return pages[i].get();
        }

        pointer DefaultPageManager::allocatePage()
        {
            Page page(new byte[PAGE_SIZE]);
            pages.push_back(page);

            ++pageCount;

            return page.get();
        }


    }
}


