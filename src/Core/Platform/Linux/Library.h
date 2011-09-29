/* 
 * File:   Library.h
 * Author: madrenegade
 *
 * Created on September 13, 2011, 11:23 AM
 */

#ifndef PLATFORM_LINUX_LIBRARY_H
#define	PLATFORM_LINUX_LIBRARY_H

#ifdef LINUX

#include <string>

namespace Platform
{

    class Library
    {
    public:
        static std::string PREFIX;
        static std::string SUFFIX;
        
        Library();
        
        void open(const char* const filename);
        void close();
        
        const void* getFunction(const char* const name);
        
        
    private:
        void* handle;
        
        void check();
    };
}
#endif

#endif	/* PLATFORM_LINUX_LIBRARY_H */

