/* 
 * File:   XmlReader.cpp
 * Author: madrenegade
 * 
 * Created on September 22, 2011, 7:54 PM
 */

#include "Utilities/IO/XmlReader.h"
#include "Utilities/functions.h"
#include "XmlAllocator.h"

#include <glog/logging.h>
#include <stdexcept>

namespace Utilities
{
    namespace IO
    {

        XmlReader::XmlReader(const boost::shared_ptr<Memory::MemoryManager>& memory,
                             const Utilities::Memory::pool_id pool,
                             const File::Handle& file)
        : data(memory->allocate<Memory::byte>(file->getSize() + 1, pool))
        {
            XmlAllocator::memory = memory;
            
            copy(file->getData(), data.get(), file->getSize());
            data[file->getSize()] = '\0';
            
            doc.reset(new Document); //, pool);
            doc->memory_pool::set_allocator(XmlAllocator::allocate, XmlAllocator::deallocate);
            doc->parse<0>(data.get());
        }

        XmlReader::~XmlReader()
        {
        }
        
        const XmlReader::Document* XmlReader::getDocument() const
        {
            return doc.get();
        }
    }
}


