/* 
 * File:   Library.cpp
 * Author: madrenegade
 * 
 * Created on September 13, 2011, 11:23 AM
 */

#ifdef LINUX
#include "Platform/Linux/Library.h"

#include <dlfcn.h>
#include <stdexcept>

namespace Platform
{
    std::string Library::PREFIX("lib");
    std::string Library::SUFFIX("so");

    Library::Library()
    : handle(0)
    {

    }

    void Library::open(const char* filename)
    {
        handle = dlopen(filename, RTLD_LAZY);

        if (handle == 0)
        {
            throw std::runtime_error(dlerror());
        }

        dlerror();
    }

    void* Library::getFunction(const char* name)
    {
#ifdef DEBUG
        void* ptr = dlsym(handle, name);

        if (ptr == 0)
        {
            throw std::runtime_error(dlerror());
        }

        return ptr;
#else
        return dlsym(handle, name);
#endif
    }

    void Library::close()
    {
        if (handle != 0)
        {
            dlclose(handle);
            handle = 0;
        }
    }
}

#endif