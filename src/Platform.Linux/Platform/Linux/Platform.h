/*
 * File:   Platform.h
 * Author: madrenegade
 *
 * Created on September 13, 2011, 12:09 PM
 */

#ifndef PLATFORM_LINUX_PLATFORM_H
#define	PLATFORM_LINUX_PLATFORM_H

#include "Platform/PlatformImpl.h"
#include <boost/shared_ptr.hpp>
#include <GL/glx.h>

namespace Platform
{
    namespace Linux
    {
        class X11EventHandler;

        class Platform : public PlatformImpl
        {
        public:
            Platform();
            virtual ~Platform();

            virtual void handleOSEvents();
            virtual unsigned int getKeysym(const char* const name) const;

            virtual boost::shared_ptr<Graphics::Window> createWindow(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager,
                    const boost::shared_ptr<Core::Events::EventManager>& eventManager,
                    const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties);

            virtual void centerMouse(const Core::Events::EventID& id, const boost::any& data);

        private:
            boost::shared_ptr<X11EventHandler> eventHandler;

            unsigned int windowWidth;
            unsigned int windowHeight;
            Display* display;
            ::Window window;
        };
    }
}


#endif	/* PLATFORM_LINUX_PLATFORM_H */

