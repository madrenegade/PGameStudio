/*
 * File:   X11EventHandler.h
 * Author: madrenegade
 *
 * Created on November 29, 2010, 6:24 PM
 */

#ifndef PLATFORM_LINUX_X11EVENTHANDLER_H
#define	PLATFORM_LINUX_X11EVENTHANDLER_H

#include <X11/Xlib.h>
#include "Core/Events/typedefs.h"

namespace Core
{
    namespace Events
    {
        class EventManager;
    }
}

namespace Platform
{
    namespace Linux
    {
        class X11Window;

        class X11EventHandler
        {
        public:
            X11EventHandler(const std::shared_ptr<Core::Events::EventManager>& eventManager, Display* display, ::Window window);
            virtual ~X11EventHandler();

            virtual void handleEvents();
            virtual unsigned int GetKeysym(const char* const name) const;

            void warpPointer(const unsigned int x, const unsigned int y);

        private:
            std::shared_ptr<Core::Events::EventManager> eventManager;
            Display* display;
            ::Window window;

            Core::Events::EventID quitEvent;
            Core::Events::EventID keyPressEvent;
            Core::Events::EventID keyReleaseEvent;
            Core::Events::EventID buttonPressEvent;
            Core::Events::EventID buttonReleaseEvent;
            Core::Events::EventID mouseMoveEvent;

            bool pointerWarped;
        };
    }
}


#endif	/* PLATFORM_LINUX_X11EVENTHANDLER_H */

