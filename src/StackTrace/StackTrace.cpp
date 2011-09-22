#include "StackTrace.h"
#include "StackFrame.h"

#include <libunwind.h>
#include <glog/logging.h>
#include <glog/raw_logging.h>

#ifdef GCC
#include <cxxabi.h>
#include <stdexcept>
#include <boost/shared_ptr.hpp>
#include <execinfo.h>
#endif

std::string demangle(const char* symbol)
{
#ifdef GCC
    size_t size;
    int status;
    char temp[256];
    char* demangled;
    
    //first, try to demangle a c++ name
    if (1 == sscanf(symbol, "%*[^(]%*[^_]%127[^)+]", temp))
    {
        if (NULL != (demangled = abi::__cxa_demangle(temp, NULL, &size, &status)))
        {
            std::string result(demangled);
            free(demangled);
            return result;
        }
    }
    //if that didn't work, try to get a regular c symbol
    if (1 == sscanf(symbol, "%127s", temp))
    {
        return temp;
    }

    //if all else fails, just return the symbol
    return symbol;
#else
    return std::string(symbol);
#endif
}

StackTrace::StackTrace(bool x)
{
    if (x)
    {
        // this code crashes sometimes at heavy load when the google profiler is used
        // this happens with libunwind and also with backtrace
#if defined GCC && !defined(X64)
        // use backtrace because it is much faster
        void* data[25];
        
        size_t size = backtrace(data, sizeof(data));

        char** symbols = backtrace_symbols(data, size);

        for (int i = 1; i < size; ++i)
        {

            //std::string s(functionName.substr(openingBrace, plus - openingBrace));
            frames.push_front(StackFrame(demangle(symbols[i])));
        }

        free(symbols);
#else

//        unw_cursor_t cursor;
//        unw_context_t uc;
//        unw_word_t ip, sp, offp;
//
//        unw_getcontext(&uc);
//        unw_init_local(&cursor, &uc);
//
//        char buffer[128];
//
//        while (unw_step(&cursor) > 0)
//        {
//            unw_get_proc_name(&cursor, buffer, 128, &offp);
//            unw_get_reg(&cursor, UNW_REG_IP, &ip);
//            unw_get_reg(&cursor, UNW_REG_SP, &sp);
//
//            frames.push_front(StackFrame(demangle("func")));
//
//            //RAW_LOG_INFO("name = %s\nip = %lx, sp = %lx\n", buffer, (long) ip, (long) sp);
//        }
#endif
    }
}

const StackTrace::Frames& StackTrace::getFrames() const
{
    return frames;
}