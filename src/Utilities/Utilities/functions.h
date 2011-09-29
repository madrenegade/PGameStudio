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
     * Demangle the name of a type or function. This function uses a compiler-specific
     * API to do the demangling.
     * @param name - The name of the function or type to demangle.
     * @return The demangled string or the input if demangling is not possible.
     */
    std::string demangle(const char* const name);

    /**
     * Fill the specified memory area with data.
     * @param start - The start address of the memory area to fill.
     * @param bytes - The amount of bytes to fill.
     * @param c - The character to put in the memory area.
     */
    void fillMemory(Memory::byte_pointer start, const size_t bytes, const char c);

    /**
     * Copy data from src to dest.
     * @param src - A pointer to the beginning of the source data.
     * @param dest - A pointer to the beginning of the destination data.
     * @param bytes - The number of bytes to copy from src to dest.
     */
    void copy(Memory::const_byte_pointer src, Memory::byte_pointer dest, const size_t bytes);

    /**
     * Count the number of bits set to zero from the right.
     * @param v - The bitset to use.
     * @return The number of bits set to zero from the right.
     */
    unsigned int countZeroBitsFromRight(const unsigned long v);

    /**
     * Count the number of bits set to one beginning from the right.
     * @param v - The bitset to use.
     * @return The number of bits set to one beginning from the right.
     */
    unsigned int countOneBitsFromRight(const unsigned long v);

    template<typename EnumType, typename InputType>
    EnumType valueOf(const InputType i)
    {
        return static_cast<EnumType>(i);
    }

    // TODO: implement this so that it can map strings to enum values
//    template<typename EnumType>
//    EnumType valueOf(const char* s)
//    {
//
//    }

    /**
     * Convert a string to the specified type.
     * @param s - The string to convert.
     * @return The string converted to the specified type.
     */
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

