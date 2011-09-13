/* 
 * File:   PlatformImpl.h
 * Author: madrenegade
 *
 * Created on September 13, 2011, 12:06 PM
 */

#ifndef PLATFORM_PLATFORMIMPL_H
#define	PLATFORM_PLATFORMIMPL_H

#include <boost/shared_ptr.hpp>

namespace Graphics
{
    class Window;
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

        virtual boost::shared_ptr<Graphics::Window> createWindow(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager,
                                                                 const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties) = 0;

    protected:
        PlatformImpl();
    };
}


#endif	/* PLATFORM_PLATFORMIMPL_H */

