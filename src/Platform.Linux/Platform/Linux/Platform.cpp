/* 
 * File:   Platform.cpp
 * Author: madrenegade
 * 
 * Created on September 13, 2011, 12:09 PM
 */

#include "Platform/Linux/Platform.h"
#include "Platform/Linux/XWindow.h"
#include "Utilities/Properties/PropertyManager.h"
#include "Utilities/Memory/MemoryManager.h"

#include <glog/logging.h>
#include <stdexcept>

using namespace Utilities::Memory;
using namespace Utilities::Properties;

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

        boost::shared_ptr<Graphics::Window> Platform::createWindow(const MemoryManager::Ptr& memoryManager,
                                                                   const PropertyManager::Ptr& properties)
        {
            unsigned int width = properties->get<unsigned int>("Window.width");
            unsigned int height = properties->get<unsigned int>("Window.height");
            unsigned int bpp = properties->get<unsigned int>("Window.bitsPerPixel");

            bool fullscreen = properties->get<bool>("Window.fullscreen");

            std::string renderer = properties->get<std::string > ("Graphics.renderer");

            // as we are under linux only OpenGL is supported
            if (renderer != "OpenGL")
            {
                throw std::logic_error("Under Linux only OpenGL ist supported");
            }

            boost::shared_ptr<Graphics::Window> window(new XWindow(memoryManager, width, height, bpp, fullscreen));
            return window;
        }
    }
}


