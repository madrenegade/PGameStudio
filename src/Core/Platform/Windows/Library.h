/* 
 * File:   Library.h
 * Author: madrenegade
 *
 * Created on September 14, 2011, 13:30 AM
 */

#ifndef PLATFORM_WINDOWS_LIBRARY_H
#define	PLATFORM_WINDOW_LIBRARY_H

#ifdef WINDOWS

#include <string>
#include <Windows.h>

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
        
        void* getFunction(const char* const name);
        
        
    private:
        HMODULE handle;
    };
}
#endif

#endif	/* PLATFORM_WINDOWS_LIBRARY_H */

