/* 
 * File:   FileSystemBackend.h
 * Author: madrenegade
 *
 * Created on September 12, 2011, 2:01 PM
 */

#ifndef UTILITIES_IO_FILESYSTEMBACKEND_H
#define	UTILITIES_IO_FILESYSTEMBACKEND_H

namespace Utilities
{
    namespace IO
    {
        enum class FileSystemBackend : unsigned char
        {
            Real,
            PhysFS
        };
    }
}

#endif	/* UTILITIES_IO_FILESYSTEMBACKEND_H */

