/*
 * File:   Platform.cpp
 * Author: madrenegade
 *
 * Created on October 2, 2011, 09:41 PM
 */

#include "Platform/Editor/Platform.h"
#include "Platform/Editor/Window.h"

#include "Utilities/Properties/PropertyManager.h"
#include "Utilities/Memory/MemoryManager.h"

#include "Core/Events/EventManager.h"

#include <glog/logging.h>
#include <stdexcept>

using namespace Utilities::Memory;
using namespace Utilities::Properties;
using namespace Core::Events;

namespace Platform
{
    namespace Editor
    {

        Platform::Platform()
        {
        }

        Platform::~Platform()
        {
        }

        void Platform::handleOSEvents()
        {
        }

        unsigned int Platform::getKeysym(const char* const) const
        {
            return 0;
        }

        boost::shared_ptr<Graphics::Window> Platform::createWindow(const MemoryManager::Ptr& memoryManager,
                const boost::shared_ptr<EventManager>&,
                const PropertyManager::Ptr& properties)
        {
            std::string renderer = properties->get<std::string > ("Graphics.renderer");

            // as we are under linux only OpenGL is supported
            if (renderer != "OpenGL")
            {
                throw std::logic_error("PGSEditor only supports OpenGL");
            }

            boost::shared_ptr<Graphics::Window> window = memoryManager->construct(Window(properties));
            return window;
        }

        void Platform::centerMouse(const Core::Events::EventID&, const boost::any&)
        {

        }
    }
}


