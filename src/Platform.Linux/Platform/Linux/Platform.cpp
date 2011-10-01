/*
 * File:   Platform.cpp
 * Author: madrenegade
 *
 * Created on September 13, 2011, 12:09 PM
 */

#include "Platform/Linux/Platform.h"
#include "Platform/Linux/XWindow.h"
#include "Platform/Linux/X11EventHandler.h"

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
    namespace Linux
    {

        Platform::Platform()
        {
            LOG(INFO) << "Platform created";
        }

        Platform::~Platform()
        {
            LOG(INFO) << "Platform destroyed";
        }

        void Platform::handleOSEvents()
        {
            eventHandler->handleEvents();
        }

        unsigned int Platform::getKeysym(const char* name) const
        {
            return eventHandler->GetKeysym(name);
        }

        boost::shared_ptr<Graphics::Window> Platform::createWindow(const MemoryManager::Ptr& memoryManager,
                                                                   const boost::shared_ptr<EventManager>& eventManager,
                                                                   const PropertyManager::Ptr& properties)
        {
            windowWidth = properties->get<unsigned int>("Window.width");
            windowHeight = properties->get<unsigned int>("Window.height");
            unsigned int bpp = properties->get<unsigned int>("Window.bitsPerPixel");

            bool fullscreen = properties->get<bool>("Window.fullscreen");

            std::string renderer = properties->get<std::string > ("Graphics.renderer");

            // as we are under linux only OpenGL is supported
            if (renderer != "OpenGL")
            {
                throw std::logic_error("Under Linux only OpenGL is supported");
            }

            XWindow* x11Window = new XWindow(memoryManager, windowWidth, windowHeight, bpp, fullscreen);
            display = x11Window->getDisplay();
            window = x11Window->getHandle();

            eventHandler.reset(new X11EventHandler(eventManager, x11Window->getDisplay(), x11Window->getHandle()));

            boost::shared_ptr<Graphics::Window> window(x11Window);

            return window;
        }

        void Platform::centerMouse(const Core::Events::EventID& id, const boost::any& data)
        {
            const unsigned int centerX = (windowWidth / 2);
            const unsigned int centerY = (windowHeight / 2);

            eventHandler->warpPointer(centerX, centerY);
        }
    }
}


