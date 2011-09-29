/* 
 * File:   PageManager.h
 * Author: madrenegade
 *
 * Created on September 10, 2011, 9:31 AM
 */

#ifndef UTILITIES_MEMORY_PAGEMANAGER_H
#define	UTILITIES_MEMORY_PAGEMANAGER_H

#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>

#include "Utilities/Memory/typedefs.h"

namespace Utilities
{
    namespace Memory
    {

        class PageManager
        {
        public:
            typedef boost::shared_ptr<PageManager> Ptr;
            
            static Ptr create(const size_t maxSize, const size_t pageSize);
            
            size_t getPageSize() const;
            size_t getUnusedPages() const;
            
            byte_pointer requestNewPage();
            
            virtual byte_pointer getPageFor(const_byte_pointer ptr) = 0;
            virtual byte_pointer getPage(const size_t i) const = 0;
            
            virtual size_t getPagesInUse() const = 0;
            
            virtual ~PageManager();
            
        protected:
            PageManager(const size_t maxSize, const size_t pageSize);
            
            virtual byte_pointer allocatePage() = 0;
            
            const size_t MAX_SIZE;
            const size_t PAGE_SIZE;
            
            const unsigned int MAX_PAGE_COUNT;
        };
    }
}


#endif	/* UTILITIES_MEMORY_PAGEMANAGER_H */

