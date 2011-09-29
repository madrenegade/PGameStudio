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

#include "Core/Events/typedefs.h"

#include "Scripting/typedefs.h"
#include "Scripting/Command.h"

#include "Utilities/Memory/typedefs.h"
#include "Utilities/Memory/STLAllocator.h"

#include <vector>

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
    class Script;

    class ScriptManager
    {
    public:
        static void addOptionsTo(const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties);

        ~ScriptManager();

        void runStartupScript();

        void runScript(const char* const name);
        void runScript(const Core::Events::EventID& id, const boost::any& data);

        void setVariable(const Core::Events::EventID& id, const boost::any& data);

        void runGarbageCollection();

        template<typename T>
        void registerFunction(const char* const name, const boost::function<T>& fn)
        {
            boost::shared_ptr<CommandT<T>> command = memory->construct(CommandT<T > (name, fn), pool);

            engine->registerFunction(name, command.get(), &CommandT<T>::callback);

            commands.push_back(command);
        }

    private:
        typedef boost::shared_ptr<Command> CommandPtr;
        typedef boost::shared_ptr<Script> ScriptPtr;
        typedef std::map<std::string, ScriptPtr> ScriptMap;

        friend class ScriptManagerFactory;
        ScriptManager(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager,
                      Utilities::Memory::pool_id pool,
                      const boost::shared_ptr<Platform::PlatformManager>& platformManager,
                      const boost::shared_ptr<Utilities::IO::FileSystem>& fileSystem,
                      const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties);

        static const std::string SCRIPT_BASE_PATH;

        std::string startupScriptName;

        const boost::shared_ptr<Utilities::Memory::MemoryManager> memory;
        const Utilities::Memory::pool_id pool;

        boost::shared_ptr<Utilities::IO::FileSystem> fileSystem;
        boost::shared_ptr<ScriptEngine> engine;

        std::vector<CommandPtr, Utilities::Memory::STLAllocator<CommandPtr>> commands;

        ScriptMap scripts;
    };
}

#endif	/* SCRIPTING_SCRIPTMANAGER_H */

