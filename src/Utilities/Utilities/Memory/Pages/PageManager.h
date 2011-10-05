/*
 * File:   PageManager.h
 * Author: madrenegade
 *
 * Created on September 10, 2011, 9:31 AM
 */

#ifndef UTILITIES_MEMORY_PAGEMANAGER_H
#define	UTILITIES_MEMORY_PAGEMANAGER_H


#include <boost/shared_array.hpp>

#include "Utilities/Memory/typedefs.h"

namespace Utilities
{
    namespace Memory
    {
        /**
         * A class for managing memory pages.
         */
        class PageManager
        {
        public:
            typedef std::shared_ptr<PageManager> Ptr;

            /**
             * Create a page manager instance using the specified settings.
             * @param maxSize - The maximum size in bytes all pages are allowed to use.
             * @param pageSize - The size in bytes of one page.
             * @return A smart pointer to the newly created page manager instance.
             */
            static Ptr create(const size_t maxSize, const size_t pageSize);

            /**
             * Get the page size.
             * @return The page size in bytes used by this instance.
             */
            size_t getPageSize() const;

            /**
             * Get the amount of pages which are not used.
             * @return The amount of pages which could potentially be allocated.
             */
            size_t getUnusedPages() const;

            /**
             * Request a new memory page. If getUnusedPages() returns zero this method throws an exception
             * because the maximum memory allowed to be used by this instance is exceeded.
             * @return A pointer to the beginning of a new memory page.
             */
            byte_pointer requestNewPage();

            /**
             * Get the starting address of the page a pointer belongs to.
             * @param ptr - The pointer to which the containing page should be found.
             * @return The starting address of the page.
             */
            virtual byte_pointer getPageFor(const_byte_pointer ptr) = 0;

            /**
             * Get the starting address of a page.
             * @param i - The index of the page.
             * @return The starting address of the page.
             */
            virtual byte_pointer getPage(const size_t i) const = 0;

            /**
             * Get the amount of pages in use.
             * @return The amount of pages currently in use.
             */
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

