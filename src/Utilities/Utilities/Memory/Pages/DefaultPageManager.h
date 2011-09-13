/* 
 * File:   PageManager.h
 * Author: madrenegade
 *
 * Created on September 10, 2011, 9:26 AM
 */

#ifndef UTILITIES_MEMORY_DEFAULTPAGEMANAGER_H
#define	UTILITIES_MEMORY_DEFAULTPAGEMANAGER_H

#include "Utilities/Memory/Pages/PageManager.h"

namespace Utilities
{
    namespace Memory
    {

        class DefaultPageManager : public PageManager
        {
        public:
            DefaultPageManager(size_t maxSize, size_t pageSize);
            
            virtual size_t getPagesInUse() const;
            
            virtual byte_pointer getPageFor(const_byte_pointer ptr);
            
            virtual byte_pointer getPage(size_t i) const;
           
        protected:
            virtual byte_pointer allocatePage();
            
        private:
            typedef boost::shared_array<byte> Page;
            std::vector<Page> pages;
            size_t pageCount;
            
            byte_pointer binaryPageSearch(const_byte_pointer ptr) const;
            
            bool dirty;
            
            byte_pointer lastPageSearchResult;
        };
    }
}

#endif	/* UTILITIES_MEMORY_DEFAULTPAGEMANAGER_H */

