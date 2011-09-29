/* 
 * File:   XmlAllocator.cpp
 * Author: madrenegade
 * 
 * Created on September 22, 2011, 9:47 PM
 */

#include "Utilities/IO/XmlAllocator.h"
#include "Utilities/Memory/MemoryManager.h"

namespace Utilities
{
    namespace IO
    {
        boost::shared_ptr<Memory::MemoryManager> XmlAllocator::memory;
        std::map<void*, size_t> XmlAllocator::allocations;

        XmlAllocator::XmlAllocator()
        {
        }

        XmlAllocator::~XmlAllocator()
        {
        }

        void* XmlAllocator::allocate(const size_t bytes)
        {
#ifdef DEBUG
            void* ptr = memory->rawAllocate<Memory::byte>(bytes, StackTrace());
#else
            void* ptr = memory->rawAllocate<Memory::byte>(bytes);
#endif
            
            allocations[ptr] = bytes;
            
            return ptr;
        }

        void XmlAllocator::deallocate(void* ptr)
        {
            memory->rawDeallocate(reinterpret_cast<Memory::const_byte_pointer>(ptr), allocations[ptr]);
            allocations.erase(ptr);
        }
    }
}


