/* 
 * File:   string.h
 * Author: madrenegade
 *
 * Created on September 8, 2011, 1:57 PM
 */

#ifndef UTILITIES_STRING_H
#define	UTILITIES_STRING_H

#include "Utilities/Memory/STLAllocator.h"
#include <string>

namespace Utilities
{
    namespace Memory
    {
        template <class T> class STLAllocator;
    }
}

typedef std::basic_string<char, std::char_traits<char>, Utilities::Memory::STLAllocator<char> > String;

#endif	/* UTILITIES_STRING_H */

