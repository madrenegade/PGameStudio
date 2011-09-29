/* 
 * File:   XmlAllocator.h
 * Author: madrenegade
 *
 * Created on September 22, 2011, 9:47 PM
 */

#ifndef UTILITIES_IO_XMLALLOCATOR_H
#define	UTILITIES_IO_XMLALLOCATOR_H

#include "Utilities/Memory/typedefs.h"
#include <cstddef>
#include <boost/shared_ptr.hpp>
#include <map>

namespace Utilities
{
    namespace Memory
    {
        class MemoryManager;
    }

    namespace IO
    {

        class XmlAllocator
        {
        public:
            static void* allocate(const size_t bytes);
            static void deallocate(void* ptr);

            static boost::shared_ptr<Memory::MemoryManager> memory;
            
        private:
            XmlAllocator();
            ~XmlAllocator();
            
            static std::map<void*, size_t> allocations;
        };
    }
}


#endif	/* UTILITIES_IO_XMLALLOCATOR_H */

