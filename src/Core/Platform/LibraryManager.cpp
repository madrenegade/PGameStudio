/*
 * File:   LibraryManager.cpp
 * Author: madrenegade
 *
 * Created on September 13, 2011, 11:20 AM
 */

#include "Platform/LibraryManager.h"
#include "Platform/Library.h"

#include "Utilities/string.h"

#include <boost/bind.hpp>

#include <glog/logging.h>
#include <list>

using namespace Utilities::Memory;

namespace Platform
{
    LibraryManager::LibraryManager(MemoryManager* const memoryManager)
        : memoryManager(memoryManager)
    {
    }

    LibraryManager::~LibraryManager()
    {
    }

    std::shared_ptr<Library> LibraryManager::load(const char* const name, const bool keepOpen)
    {
        String fullName(Library::PREFIX.c_str(), Library::PREFIX.size());
        fullName.append(name);
        fullName.append(".");
        fullName.append(Library::SUFFIX.c_str(), Library::SUFFIX.size());

        LOG(INFO) << "Loading library " << fullName;

        std::shared_ptr<Library> lib = memoryManager->construct(Library(), boost::bind(&LibraryManager::unload, this, _1));

        if(keepOpen)
        {
            loadedLibraries.push_front(lib);
        }

        lib->open(fullName.c_str());

        return lib;
    }

    void LibraryManager::unload(Library* const lib)
    {
        lib->close();
    }
}
