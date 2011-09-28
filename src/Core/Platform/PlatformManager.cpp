/* 
 * File:   PlatformManager.cpp
 * Author: madrenegade
 * 
 * Created on September 13, 2011, 11:20 AM
 */

#include <boost/function.hpp>

#include "Platform/PlatformManager.h"
#include "Platform/Linux/Library.h"
#include "Platform/PlatformImpl.h"

#include "Utilities/Properties/PropertyManager.h"

#include "Core/Events/EventManager.h"

using namespace Utilities::Memory;
using namespace Utilities::Properties;
using namespace Core::Events;

typedef boost::shared_ptr<Platform::PlatformImpl> (*CreateFn)(const MemoryManager::Ptr&);

namespace Platform
{

    PlatformManager::PlatformManager(const MemoryManager::Ptr& memory,
                                     const boost::shared_ptr<EventManager>& eventManager,
                                     const PropertyManager::Ptr& properties)
    : memoryManager(memory), eventManager(eventManager), properties(properties)
    {
        libraryManager = memory->construct(LibraryManager());

        boost::shared_ptr<Library> platformLib = libraryManager->load("Platform.Linux");

        CreateFn create = reinterpret_cast<CreateFn> (platformLib->getFunction("create"));

        impl = create(memory);
    }

    PlatformManager::~PlatformManager()
    {
    }
    
    void PlatformManager::handleOSEvents()
    {
        impl->handleOSEvents();
    }
    
    unsigned int PlatformManager::getKeysym(const char* name) const
    {
        return impl->getKeysym(name);
    }

    boost::shared_ptr<Graphics::Window> PlatformManager::createWindow()
    {
        if(properties->get<std::string>("Graphics.renderer") == "NULL")
        {
            // null-renderer is meant for server usage
            // so all window and drawing functions result in doing nothing
            // input handling is done via command line
            
            throw std::runtime_error("Null-Renderer not yet implemented");
        }
        
        boost::shared_ptr<Graphics::Window> window = impl->createWindow(memoryManager, eventManager, properties);
        this->window = window.get();
        
        return window;
    }
    
    Graphics::Window* PlatformManager::getWindow()
    {
        return window;
    }
    
    LibraryManager* PlatformManager::libraries() const
    {
        return libraryManager.get();
    }
}


