/* 
 * File:   File.h
 * Author: madrenegade
 *
 * Created on September 12, 2011, 5:32 PM
 */

#ifndef UTILITIES_FILE_H
#define	UTILITIES_FILE_H

#include "Utilities/Memory/typedefs.h"
#include <boost/shared_array.hpp>

namespace Utilities
{
    namespace IO
    {

        class File
        {
        public:
            File(const boost::shared_array<Memory::byte>& data, size_t size);
            
            Memory::byte_pointer getData() const;
            size_t getSize() const;
            
        private:
            boost::shared_array<Memory::byte> data;
            size_t size;
        };
    }
}


#endif	/* UTILITIES_FILE_H */

