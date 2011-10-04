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

    std::string demangle(const char* const name)
    {
#ifdef GCC
        int status;

        boost::shared_ptr<char> res(abi::__cxa_demangle(DCHECK_NOTNULL(name),
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

    void fillMemory(Memory::byte_pointer start, const size_t bytes, const char c)
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

        std::fill_n(start, bytes, c);
    }

    void copy(Memory::const_byte_pointer src, Memory::byte_pointer dest, const size_t bytes)
    {
        std::copy(DCHECK_NOTNULL(src), &src[bytes], DCHECK_NOTNULL(dest));
    }

    unsigned int countZeroBitsFromRight(const unsigned long v)
    {
#ifdef GCC
        return v == 0 ? Memory::ULONG_BITS : __builtin_ctzl(v);
#elif MSVC
        unsigned long c = 0;
        _BitScanForward64(&c, v);
        return c;
#endif
    }

    unsigned int countOneBitsFromRight(const unsigned long v)
    {
        return countZeroBitsFromRight(~v);
    }
}
