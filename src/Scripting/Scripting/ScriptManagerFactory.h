/* 
 * File:   ScriptManagerFactory.h
 * Author: madrenegade
 *
 * Created on September 15, 2011, 4:56 PM
 */

#ifndef SCRIPTING_SCRIPTMANAGERFACTORY_H
#define	SCRIPTING_SCRIPTMANAGERFACTORY_H

#include <boost/shared_ptr.hpp>

namespace Utilities
{
    namespace Memory
    {
        class Pool;
        class MemoryManager;
    }

    namespace Properties
    {
        class PropertyManager;
    }

    namespace IO
    {
        class FileSystem;
    }
}

namespace Platform
{
    class PlatformManager;
}

namespace Scripting
{
    class ScriptManager;
    
    class ScriptManagerFactory
    {
    public:
        static boost::shared_ptr<ScriptManager> create(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager,
                                                       const boost::shared_ptr<Platform::PlatformManager>& platformManager,
                                                       const boost::shared_ptr<Utilities::IO::FileSystem>& fileSystem,
                                                       const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties);

    private:
        ScriptManagerFactory();
        ~ScriptManagerFactory();
        
        static boost::shared_ptr<Utilities::Memory::Pool> createMemoryPool(const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties);
    };
}

#endif	/* SCRIPTING_SCRIPTMANAGERFACTORY_H */

