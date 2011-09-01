#include "Utilities/functions.h"

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
}
