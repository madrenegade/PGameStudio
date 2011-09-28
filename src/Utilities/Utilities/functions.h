/* 
 * File:   functions.h
 * Author: madrenegade
 *
 * Created on September 1, 2011, 3:01 PM
 */

#ifndef UTILITIES_FUNCTIONS_H
#define	UTILITIES_FUNCTIONS_H

#include "Utilities/Memory/typedefs.h"
#include <string>
#include <sstream>

namespace Utilities
{
    /**
     * uses compiler specific api to demangle type and function names
     * @param name
     * @return 
     */
    std::string demangle(const char* name);
    
    /**
     * fill the specified memory area with data
     * @param start - start address of the memory area to fill
     * @param bytes - amount of bytes to fill
     * @param c - the character to put in the memory area
     */
    void fillMemory(Memory::byte_pointer start, size_t bytes, char c);
    
    /**
     * Copies n bytes from src to dest.
     * @param src - the source data
     * @param dest - the destination
     * @param n - the number of bytes to copy
     */
    void copy(Memory::const_byte_pointer src, Memory::byte_pointer dest, size_t n);
    
    /**
     * count the number of bits set to zero from the right
     * @param v the bitset to use
     * @return the number of bits set to zero from the right
     */
    int countZeroBitsFromRight(unsigned long v);
    
    int countOneBitsFromRight(unsigned long v);
    
    template<typename EnumType, typename InputType>
    EnumType valueOf(InputType i)
    {
        return static_cast<EnumType>(i);
    }
    
    // TODO: implement this so that it can map strings to enum values
//    template<typename EnumType>
//    EnumType valueOf(const char* s)
//    {
//        
//    }
    
    template<typename T>
    T convertString(const char* const s)
    {
        T value;
        std::stringstream stream;
        stream << s;
        stream >> value;
        
        return value;
    }
}

#endif	/* UTILITIES_FUNCTIONS_H */

