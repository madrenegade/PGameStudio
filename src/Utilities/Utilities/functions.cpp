#include "Utilities/functions.h"
#include "Utilities/Memory/constants.h"

#ifdef GCC
#include <cxxabi.h>
#endif

namespace Utilities
{

    std::string demangle(const char* name)
    {
#ifdef GCC
        char buf[1024];
        size_t size = sizeof (buf);
        int status;

        char* res = abi::__cxa_demangle(name,
            buf,
            &size,
            &status);

        return std::string(res);
#else
        return std::string(name);
#endif
    }

    void fillMemory(Memory::pointer start, size_t bytes, char c)
    {
        for (size_t i = 0; i < bytes; ++i)
        {
            start[i] = c;
        }
    }

    int countZeroBitsFromRight(unsigned long v)
    {
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
    }
}
