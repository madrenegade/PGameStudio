/* 
 * File:   ScriptManager.h
 * Author: madrenegade
 *
 * Created on September 14, 2011, 6:48 PM
 */

#ifndef SCRIPTING_SCRIPTMANAGER_H
#define	SCRIPTING_SCRIPTMANAGER_H

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

#include "Scripting/typedefs.h"
#include "Scripting/Command.h"

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

#include <iostream>
#include <boost/mpl/for_each.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/any.hpp>
#include <boost/bind.hpp>
#include <vector>

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

        template<typename T>
        void registerFunction(const char* name, const boost::function<T>& fn)
        {
            boost::shared_ptr<CommandT<T>> command(new CommandT<T>(name, fn));
            
            engine->registerFunction(name, command.get(), &CommandT<T>::callback);
            
            commands.push_back(command);
        }

    private:
        static const std::string SCRIPT_BASE_PATH;

        std::string startupScriptName;

        boost::shared_ptr<Utilities::Memory::MemoryManager> memory;
        boost::shared_ptr<Utilities::IO::FileSystem> fileSystem;

        boost::shared_ptr<ScriptEngine> engine;
        
        std::vector<boost::shared_ptr<Command>> commands;
    };
}

#endif	/* SCRIPTING_SCRIPTMANAGER_H */

