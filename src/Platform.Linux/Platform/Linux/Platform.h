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
        };
    }
}


#endif	/* PLATFORM_LINUX_PLATFORM_H */

