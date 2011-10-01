/*
 * File:   Library.cpp
 * Author: madrenegade
 *
 * Created on September 14, 2011, 13:30 AM
 */

#ifdef WINDOWS
#include "Platform/Windows/Library.h"

#include <glog/logging.h>

namespace Platform
{
    std::string Library::PREFIX("");
    std::string Library::SUFFIX("dll");

    Library::Library()
        : handle(0)
    {

    }

    void Library::open(const char* const filename)
    {
        handle = LoadLibrary(filename);

        if (handle == 0)
        {
            DWORD error = GetLastError();
            throw std::runtime_error("Could not load DLL");
        }
    }

    void* Library::getFunction(const char* const name)
    {
#ifdef DEBUG
        const void* ptr = GetProcAddress(handle, name);

        if (ptr == 0)
        {
            throw std::runtime_error("Could not get function pointer");
        }

        return ptr;
#else
        return GetProcAddress(handle, name);
#endif
    }

    void Library::close()
    {
        if (handle != 0)
        {
            if(!FreeLibrary(handle))
            {
                LOG(WARNING) << "Could not free dll: " << GetLastError();
            }

            handle = 0;
        }
    }
}

#endif
