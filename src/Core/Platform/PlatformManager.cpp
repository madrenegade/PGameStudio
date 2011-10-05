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

typedef std::shared_ptr<Platform::PlatformImpl> (*CreateFn)(const MemoryManager::Ptr&);

namespace Platform
{

    void PlatformManager::addOptionsTo(const PropertyManager::Ptr& properties)
    {
        po::options_description options("Platform options");

        options.add_options()
#ifdef LINUX
        ("Platform.plugin", po::value<std::string>()->default_value("Linux"), "The platform plugin to use");
#endif

        properties->addOptions(options);
    }

    PlatformManager::PlatformManager(const MemoryManager::Ptr& memory,
                                     const std::shared_ptr<EventManager>& eventManager,
                                     const PropertyManager::Ptr& properties)
        : memoryManager(memory), eventManager(eventManager), properties(properties)
    {
        libraryManager = memory->construct(LibraryManager(memory));

        String platformPlugin("Platform.");
        platformPlugin.append(properties->get<std::string > ("Platform.plugin").c_str());

        platformLibrary = libraryManager->load(platformPlugin.c_str());

        // NOTE: pointer-to-function and pointer-to-object conversion gives unfixable warning
        CreateFn create = reinterpret_cast<CreateFn> (platformLibrary->getFunction("create"));

        impl = create(memory);

        const Core::Events::EventID centerMouse = eventManager->getEventID("CENTER_MOUSE");
        eventManager->registerEventHandler(centerMouse, boost::bind(&PlatformImpl::centerMouse, impl.get(), _1, _2));
    }

    PlatformManager::~PlatformManager()
    {
    }

    void PlatformManager::handleOSEvents()
    {
        impl->handleOSEvents();
    }

    unsigned int PlatformManager::getKeysym(const char* const name) const
    {
        return impl->getKeysym(name);
    }

    std::shared_ptr<Graphics::Window> PlatformManager::createWindow()
    {
        if (properties->get<std::string>("Graphics.renderer") == "NULL")
        {
            // null-renderer is meant for server usage
            // so all window and drawing functions result in doing nothing
            // input handling is done via command line
            throw std::runtime_error("Null-Renderer not yet implemented");
        }

        std::shared_ptr<Graphics::Window> window = impl->createWindow(memoryManager, eventManager, properties);
        this->window = window.get();

        return window;
    }

    Graphics::Window* PlatformManager::getWindow() const
    {
        return window;
    }

    LibraryManager* PlatformManager::libraries() const
    {
        return libraryManager.get();
    }
}


