/* 
 * File:   File.cpp
 * Author: madrenegade
 * 
 * Created on September 12, 2011, 5:32 PM
 */

#include "Utilities/IO/File.h"

namespace Utilities
{
    namespace IO
    {
        File::File()
        {
            
        }

        File::File(const boost::shared_array<Memory::byte>& data, size_t size)
        : data(data), size(size)
        {

        }

        Memory::byte_pointer File::getData() const
        {
            return data.get();
        }
        
        size_t File::getSize() const
        {
            return size;
        }
    }
}

