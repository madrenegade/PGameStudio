/* 
 * File:   Platform.h
 * Author: madrenegade
 *
 * Created on September 13, 2011, 12:09 PM
 */

#ifndef PLATFORM_LINUX_PLATFORM_H
#define	PLATFORM_LINUX_PLATFORM_H

#include "Platform/PlatformImpl.h"

namespace Platform
{
    namespace Linux
    {

        class Platform : public PlatformImpl
        {
        public:
            Platform();
            virtual ~Platform();

            virtual boost::shared_ptr<Graphics::Window> createWindow(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager,
                                                                     const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties);
        };
    }
}


#endif	/* PLATFORM_LINUX_PLATFORM_H */

