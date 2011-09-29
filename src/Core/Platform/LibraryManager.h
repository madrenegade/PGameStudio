/* 
 * File:   LibraryManager.h
 * Author: madrenegade
 *
 * Created on September 13, 2011, 11:20 AM
 */

#ifndef PLATFORM_LIBRARYMANAGER_H
#define	PLATFORM_LIBRARYMANAGER_H

#include <boost/shared_ptr.hpp>
#include <list>

#include "Utilities/Memory/STLAllocator.h"

namespace Platform
{
    class Library;
    
    class LibraryManager
    {
    public:
        LibraryManager(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager);
        ~LibraryManager();
        
        boost::shared_ptr<Library> load(const char* const name);
        
    private:
        void unload(Library* const lib);
        
        const boost::shared_ptr<Utilities::Memory::MemoryManager> memoryManager;
        
        typedef boost::shared_ptr<Library> LibPtr;
        
        typedef std::list<LibPtr, Utilities::Memory::STLAllocator<LibPtr>> LibraryList;
        LibraryList loadedLibraries;
    };
}

#endif	/* PLATFORM_LIBRARYMANAGER_H */

