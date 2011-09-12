/* 
 * File:   FileNotFoundException.cpp
 * Author: madrenegade
 * 
 * Created on September 12, 2011, 4:48 PM
 */

#include "Utilities/IO/Exceptions/FileNotFoundException.h"

namespace Utilities
{
    namespace IO
    {

        FileNotFoundException::FileNotFoundException(const std::string& path)
        : std::logic_error(path)
        {

        }
    }
}

