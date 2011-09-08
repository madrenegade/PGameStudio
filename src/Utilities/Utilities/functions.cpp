#include "Utilities/functions.h"
#include "Utilities/Memory/constants.h"
#include "Utilities/Memory/STLAllocator.h"

#include <boost/shared_ptr.hpp>
#include <glog/logging.h>
#include <glog/raw_logging.h>

#ifdef GCC
#include <cxxabi.h>
#include <stdexcept>
#endif

namespace Utilities
{
 
    std::string demangle(const char* name)
    {
#ifdef GCC
        int status;

        boost::shared_ptr<char> res(abi::__cxa_demangle(name,
            0,
            0,
            &status), free);
        
        if(status != 0)
        {
            RAW_LOG_ERROR("Demangling failed with status: %i", status);
            
            return std::string(name);
        }
        
        return std::string(res.get());
#else
        return std::string(name);
#endif
    }

    void fillMemory(Memory::pointer start, size_t bytes, char c)
    {
#ifdef DEBUG
        if(start == 0)
        {
            throw std::invalid_argument("start pointer");
        }
        
        if(bytes == 0)
        {
            throw std::invalid_argument("bytes must not be zero");
        }
#endif
        
        for (size_t i = 0; i < bytes; ++i)
        {
            start[i] = c;
        }
    }

    int countZeroBitsFromRight(unsigned long v)
    {
#ifdef GCC
        return v == 0 ? Memory::ULONG_BITS : __builtin_ctzl(v);
#else #error "Does not work"
        unsigned int c = Memory::ULONG_BITS;

        v &= -static_cast<long> (v);
        if (v) c--;
        if (v & 0xFFFFFFFF) c -= 32; // FIXME: execute only for 64 bits
        if (v & 0x0000FFFF) c -= 16;
        if (v & 0x00FF00FF) c -= 8;
        if (v & 0x0F0F0F0F) c -= 4;
        if (v & 0x33333333) c -= 2;
        if (v & 0x55555555) c -= 1;

        return c;
#endif
    }
}
