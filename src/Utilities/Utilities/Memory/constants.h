/* 
 * File:   constants.h
 * Author: madrenegade
 *
 * Created on September 1, 2011, 3:19 PM
 */

#ifndef UTILITIES_MEMORY_CONSTANTS_H
#define	UTILITIES_MEMORY_CONSTANTS_H

namespace Utilities
{
    namespace Memory
    {
        const size_t Byte = 1;
        const size_t KByte = 1024 * Byte;
        const size_t MByte = 1024 * KByte;
        const size_t GByte = 1024 * MByte;
        
        const char ALLOCATED = 'a';
        const char EMPTY = 'e';
    }
}

#endif	/* UTILITIES_MEMORY_CONSTANTS_H */

