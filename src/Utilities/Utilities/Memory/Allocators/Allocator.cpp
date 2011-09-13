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
#include "Utilities/Memory/Pages/PageManager.h"

#include <glog/logging.h>
#include <glog/raw_logging.h>
#include "Utilities/functions.h"

namespace Utilities
{
    namespace Memory
    {

        Allocator::Allocator(const boost::shared_ptr<PageManager>& pageManager, size_t blockSize)
        : pageManager(pageManager), memoryUsage(0), BLOCK_SIZE(blockSize)
        {
            if(pageManager->getPageSize() % blockSize != 0)
            {
                RAW_LOG_ERROR("Page size: %i\nBlock size: %i\nRest: %i", pageManager->getPageSize(), blockSize, pageManager->getPageSize() % blockSize);
                
                throw std::invalid_argument("Page size must be multiple of the block size");
            }
            
            if(blockSize % BITS_PER_BYTE != 0)
            {
                RAW_LOG_ERROR("Block size: %i\nRest: %i", blockSize, blockSize % BITS_PER_BYTE);
                
                throw std::invalid_argument("Block size must be multiple of BITS_PER_BYTE");
            }
        }

        bool Allocator::contains(const_byte_pointer ptr) const
        {
            try
            {
                pageManager->getPageFor(ptr);
                
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
    }
}
