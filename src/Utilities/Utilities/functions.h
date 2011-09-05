/* 
 * File:   functions.h
 * Author: madrenegade
 *
 * Created on September 1, 2011, 3:01 PM
 */

#ifndef UTILITIES_FUNCTIONS_H
#define	UTILITIES_FUNCTIONS_H

#include <string>
#include "Utilities/Memory/typedefs.h"

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
    void fillMemory(Memory::pointer start, size_t bytes, char c);
    
    /**
     * count the number of bits set to zero from the right
     * @param v the bitset to use
     * @return the number of bits set to zero from the right
     */
    int countZeroBitsFromRight(unsigned long v);
    
    /**
     * reverse the bits
     * @param v - input bits to be reversed
     * @return bits of v reversed
     */
    unsigned long reverseBits(unsigned long v);
}

#endif	/* UTILITIES_FUNCTIONS_H */

