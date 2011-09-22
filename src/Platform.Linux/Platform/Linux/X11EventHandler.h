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
            X11EventHandler(const boost::shared_ptr<Core::Events::EventManager>& eventManager, Display* display);
            virtual ~X11EventHandler();

            virtual void handleEvents();
//            virtual unsigned int GetKeysym(const char* const name) const;

        private:
            boost::shared_ptr<Core::Events::EventManager> eventManager;
            Display* display;

            Core::Events::EventID quitEvent;
            Core::Events::EventID keyPressEvent;
            Core::Events::EventID keyReleaseEvent;
            Core::Events::EventID buttonPressEvent;
            Core::Events::EventID buttonReleaseEvent;
        };
    }
}


#endif	/* PLATFORM_LINUX_X11EVENTHANDLER_H */

