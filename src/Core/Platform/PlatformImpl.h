/*
 * File:   PlatformImpl.h
 * Author: madrenegade
 *
 * Created on September 13, 2011, 12:06 PM
 */

#ifndef PLATFORM_PLATFORMIMPL_H
#define	PLATFORM_PLATFORMIMPL_H

#include <boost/shared_ptr.hpp>
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

        virtual boost::shared_ptr<Graphics::Window> createWindow(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager,
                const boost::shared_ptr<Core::Events::EventManager>& eventManager,
                const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties) = 0;

        virtual void centerMouse(const Core::Events::EventID& id, const boost::any& data);

    protected:
        PlatformImpl();
    };
}


#endif	/* PLATFORM_PLATFORMIMPL_H */

