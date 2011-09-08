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
    : type(sample_type::new_frame), stacktrace(false)
    {

    }

    sample::sample(const StackTrace& stacktrace, size_t bytes)
    : type(sample_type::allocation), stacktrace(stacktrace), allocatedBytes(bytes)
    {

    }
    
    sample_type sample::getType() const
    {
        return type;
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

