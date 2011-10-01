/*
 * File:   PageManager.cpp
 * Author: madrenegade
 *
 * Created on September 10, 2011, 9:31 AM
 */

#include "Utilities/Memory/Pages/PageManager.h"
#include "Utilities/Memory/Pages/DefaultPageManager.h"
#include "Utilities/Memory/Exceptions/OutOfMemoryException.h"

#include <glog/logging.h>
#include <glog/raw_logging.h>
#include <stdexcept>

namespace Utilities
{
    namespace Memory
    {

        PageManager::Ptr PageManager::create(const size_t maxSize, const size_t pageSize)
        {
            return Ptr(new DefaultPageManager(maxSize, pageSize));
        }

        PageManager::PageManager(const size_t maxSize, const size_t pageSize)
        : MAX_SIZE(maxSize), PAGE_SIZE(pageSize), MAX_PAGE_COUNT(maxSize / pageSize)
        {
            if (maxSize % pageSize != 0)
            {
                RAW_LOG_ERROR("Pool size: %li\nPage size: %li\nRest: %li", maxSize, pageSize, maxSize % pageSize);

                throw std::invalid_argument("Pool size must be multiple of the page size");
            }
        }

        PageManager::~PageManager()
        {

        }

        size_t PageManager::getPageSize() const
        {
            return PAGE_SIZE;
        }

        size_t PageManager::getUnusedPages() const
        {
            return MAX_PAGE_COUNT - getPagesInUse();
        }

        byte_pointer PageManager::requestNewPage()
        {
            if (getPagesInUse() == MAX_PAGE_COUNT)
            {
                RAW_LOG_FATAL("Max amount of pages exceeded: %i", MAX_PAGE_COUNT);
            }

            return allocatePage();
        }
    }
}
