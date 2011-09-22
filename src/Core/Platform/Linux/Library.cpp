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

#include <glog/logging.h>

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
            check();
        }
    }

    void* Library::getFunction(const char* name)
    {
#ifdef DEBUG
        void* ptr = dlsym(handle, name);

        if (ptr == 0)
        {
            check();
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
            if(dlclose(handle) != 0)
            {
                check();
            }
            
            handle = 0;
        }
    }
    
    void Library::check()
    {
        const char* error = dlerror();
        
        if(error != 0)
        {
            LOG(FATAL) << "Dynamic library error: " << error;
        }
    }
}

#endif