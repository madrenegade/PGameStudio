/* 
 * File:   PlatformManager.cpp
 * Author: madrenegade
 * 
 * Created on September 13, 2011, 11:20 AM
 */

#include <boost/function.hpp>

#include "Platform/PlatformManager.h"
#include "Linux/Library.h"
#include "PlatformImpl.h"

typedef boost::shared_ptr<Platform::PlatformImpl> (*CreateFn)(const Utilities::Memory::MemoryManager::Ptr&);

namespace Platform
{

    PlatformManager::PlatformManager(const Utilities::Memory::MemoryManager::Ptr& memory, 
                        const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties)
    {
        libraryManager = memory->construct(LibraryManager());
        
        boost::shared_ptr<Library> platformLib = libraryManager->load("Platform.Linux");
        
        CreateFn create = reinterpret_cast<CreateFn>(platformLib->getFunction("create"));
        
        impl = create(memory);
    }

    PlatformManager::~PlatformManager()
    {
    }
}


