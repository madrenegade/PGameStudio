/* 
 * File:   PlatformManager.h
 * Author: madrenegade
 *
 * Created on September 13, 2011, 11:20 AM
 */

#ifndef PLATFORM_PLATFORMMANAGER_H
#define	PLATFORM_PLATFORMMANAGER_H

#include <boost/shared_ptr.hpp>
#include "Platform/LibraryManager.h"

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

    class PlatformImpl;
    
    class PlatformManager
    {
    public:
        PlatformManager(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memory, 
                        const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties);
        ~PlatformManager();
        
    private:
        boost::shared_ptr<LibraryManager> libraryManager;
        
        boost::shared_ptr<PlatformImpl> impl;
    };
}

#endif	/* PLATFORM_PLATFORMMANAGER_H */

