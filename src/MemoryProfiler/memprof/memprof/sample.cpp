/* 
 * File:   sample.cpp
 * Author: madrenegade
 * 
 * Created on September 7, 2011, 11:58 AM
 */

#include "memprof/sample.h"

namespace memprof
{

    sample::sample()
    : stacktrace(false)
    {

    }

    sample::sample(const StackTrace& stacktrace, size_t bytes)
    : stacktrace(stacktrace), allocatedBytes(bytes)
    {

    }

    const StackTrace& sample::getStackTrace() const
    {
        return stacktrace;
    }
    
    size_t sample::getAllocatedBytes() const
    {
        return allocatedBytes;
    }
}

