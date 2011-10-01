/*
 * File:   FileNotFoundException.h
 * Author: madrenegade
 *
 * Created on September 12, 2011, 4:48 PM
 */

#ifndef UTILITIES_IO_FILENOTFOUNDEXCEPTION_H
#define	UTILITIES_IO_FILENOTFOUNDEXCEPTION_H

#include <stdexcept>

namespace Utilities
{
    namespace IO
    {

        class FileNotFoundException : public std::logic_error
        {
        public:
            explicit FileNotFoundException(const std::string& path);
        };
    }
}


#endif	/* UTILITIES_IO_FILENOTFOUNDEXCEPTION_H */

