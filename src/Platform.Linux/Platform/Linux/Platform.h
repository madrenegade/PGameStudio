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

            virtual boost::shared_ptr<Graphics::Window> createWindow(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager,
                                                                     const boost::shared_ptr<Core::Events::EventManager>& eventManager,
                                                                     const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties);
            
        private:
            boost::shared_ptr<X11EventHandler> eventHandler;
        };
    }
}


#endif	/* PLATFORM_LINUX_PLATFORM_H */

