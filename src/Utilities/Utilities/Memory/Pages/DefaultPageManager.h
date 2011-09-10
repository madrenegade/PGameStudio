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
            
            virtual pointer getPageFor(const_pointer ptr);
            
            virtual pointer getPage(size_t i) const;
           
        protected:
            virtual pointer allocatePage();
            
        private:
            typedef boost::shared_array<byte> Page;
            std::vector<Page> pages;
            size_t pageCount;
            
            bool dirty;
        };
    }
}

#endif	/* UTILITIES_MEMORY_DEFAULTPAGEMANAGER_H */

