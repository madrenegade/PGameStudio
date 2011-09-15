/* 
 * File:   ScriptManager.h
 * Author: madrenegade
 *
 * Created on September 14, 2011, 6:48 PM
 */

#ifndef SCRIPTING_SCRIPTMANAGER_H
#define	SCRIPTING_SCRIPTMANAGER_H

#include <boost/shared_ptr.hpp>

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
    class ScriptEngine;
    
    class ScriptManager
    {
    public:
        static void addOptionsTo(const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties);
        
        ScriptManager(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager,
                      const boost::shared_ptr<Platform::PlatformManager>& platformManager,
                      const boost::shared_ptr<Utilities::IO::FileSystem>& fileSystem,
                      const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties);
        ~ScriptManager();
        
        void runStartupScript();
        
        void runScript(const char* name);
        
    private:
        static const std::string SCRIPT_BASE_PATH;
        
        std::string startupScriptName;
        
        boost::shared_ptr<Utilities::Memory::MemoryManager> memory;
        boost::shared_ptr<Utilities::IO::FileSystem> fileSystem;
        
        boost::shared_ptr<ScriptEngine> engine;
    };
}

#endif	/* SCRIPTING_SCRIPTMANAGER_H */

