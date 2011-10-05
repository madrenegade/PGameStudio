/*
 * File:   Platform.h
 * Author: madrenegade
 *
 * Created on October 2, 2011, 9:41 PM
 */

#ifndef PLATFORM_EDITOR_PLATFORM_H
#define	PLATFORM_EDITOR_PLATFORM_H

#include "Platform/PlatformImpl.h"


namespace Platform
{
    namespace Editor
    {
        class Platform : public PlatformImpl
        {
        public:
            Platform();
            virtual ~Platform();

            virtual void handleOSEvents();
            virtual unsigned int getKeysym(const char* const name) const;

            virtual std::shared_ptr<Graphics::Window> createWindow(const std::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager,
                    const std::shared_ptr<Core::Events::EventManager>& eventManager,
                    const std::shared_ptr<Utilities::Properties::PropertyManager>& properties);

            virtual void centerMouse(const Core::Events::EventID& id, const boost::any& data);
        };
    }
}


#endif	/* PLATFORM_EDITOR_PLATFORM_H */

