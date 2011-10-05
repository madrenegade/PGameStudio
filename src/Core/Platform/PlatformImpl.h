/*
 * File:   PlatformImpl.h
 * Author: madrenegade
 *
 * Created on September 13, 2011, 12:06 PM
 */

#ifndef PLATFORM_PLATFORMIMPL_H
#define	PLATFORM_PLATFORMIMPL_H


#include "Core/Events/typedefs.h"

namespace Graphics
{
    class Window;
    class Renderer;
}

namespace Core
{
    namespace Events
    {
        class EventManager;
    }
}

namespace Utilities
{
    namespace Memory
    {
        class MemoryManager;
    }

    namespace Properties
    {
        class PropertyManager;
    }
}

namespace Platform
{

    class PlatformImpl
    {
    public:
        virtual ~PlatformImpl();

        virtual void handleOSEvents() = 0;
        virtual unsigned int getKeysym(const char* const) const = 0;

        virtual std::shared_ptr<Graphics::Window> createWindow(Utilities::Memory::MemoryManager* const memoryManager,
                Core::Events::EventManager* const eventManager,
                const Utilities::Properties::PropertyManager* const properties) = 0;

        virtual void centerMouse(const Core::Events::EventID& id, const boost::any& data);

    protected:
        PlatformImpl();
    };
}


#endif	/* PLATFORM_PLATFORMIMPL_H */

