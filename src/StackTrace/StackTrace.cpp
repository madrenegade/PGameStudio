#include "StackTrace.h"
#include "StackFrame.h"

#include <libunwind.h>
#include <glog/logging.h>
#include <glog/raw_logging.h>

#ifdef GCC
#include <cxxabi.h>
#include <stdexcept>
#include <boost/shared_ptr.hpp>
#endif

std::string demangle(const char* name)
{
#ifdef GCC
    int status;

    boost::shared_ptr<char> res(abi::__cxa_demangle(name,
        0,
        0,
        &status), free);

    if (status != 0)
    {
        RAW_LOG_ERROR("Demangling failed with status: %i", status);

        return std::string(name);
    }

    return std::string(res.get());
#else
    return std::string(name);
#endif
}

StackTrace::StackTrace(bool x)
{
    if (x)
    {
        unw_cursor_t cursor;
        unw_context_t uc;
        unw_word_t ip, sp, offp;

        unw_getcontext(&uc);
        unw_init_local(&cursor, &uc);

        char buffer[128];

        while (unw_step(&cursor) > 0)
        {
            unw_get_proc_name(&cursor, buffer, 128, &offp);
            unw_get_reg(&cursor, UNW_REG_IP, &ip);
            unw_get_reg(&cursor, UNW_REG_SP, &sp);

            frames.push_front(StackFrame(demangle(buffer)));

            //RAW_LOG_INFO("name = %s\nip = %lx, sp = %lx\n", buffer, (long) ip, (long) sp);
        }
    }
}

const std::list<StackFrame>& StackTrace::getFrames() const
{
    return frames;
}