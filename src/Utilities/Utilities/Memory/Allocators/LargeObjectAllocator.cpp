/*
 * File:   LargeObjectAllocator.cpp
 * Author: madrenegade
 *
 * Created on September 2, 2011, 11:00 PM
 */

#include "Utilities/Memory/Allocators/LargeObjectAllocator.h"
#include "MediumObjectAllocator.h"
#include <stdexcept>

namespace Utilities
{
    namespace Memory
    {
        LargeObjectAllocator::LargeObjectAllocator(const boost::shared_ptr<PageManager>& pageManager, const size_t blockSize)
            : MediumObjectAllocator(pageManager, blockSize)
        {

        }
    }
}

