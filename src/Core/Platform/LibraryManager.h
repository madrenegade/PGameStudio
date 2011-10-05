/*
 * File:   LibraryManager.h
 * Author: madrenegade
 *
 * Created on September 13, 2011, 11:20 AM
 */

#ifndef PLATFORM_LIBRARYMANAGER_H
#define	PLATFORM_LIBRARYMANAGER_H

#include <memory>
#include <list>

#include "Utilities/Memory/STLAllocator.h"

namespace Platform
{
    class Library;

    class LibraryManager
    {
    public:
        LibraryManager(Utilities::Memory::MemoryManager* const memoryManager);
        ~LibraryManager();

        /**
         * Load a shared library with the specified name. Prefixes and suffixes are autmatically added
         * to the name depending on the platform.
         * @param name - The basename of the library to load.
         * @param keepOpen - True if the library should be kept open, false otherwise.
         * Not keeping the library open means that the library will be closed when there are
         * no more refences to the library.
         * @return A pointer to the library.
         */
        std::shared_ptr<Library> load(const char* const name, const bool keepOpen = false);

    private:
        void unload(Library* const lib);

        Utilities::Memory::MemoryManager* const memoryManager;

        typedef std::shared_ptr<Library> LibPtr;

        typedef std::list<LibPtr, Utilities::Memory::STLAllocator<LibPtr>> LibraryList;
        LibraryList loadedLibraries;
    };
}

#endif	/* PLATFORM_LIBRARYMANAGER_H */

