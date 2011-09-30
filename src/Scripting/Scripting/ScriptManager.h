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
#include <boost/type_traits.hpp>

#include "Core/Events/typedefs.h"

#include "Scripting/typedefs.h"

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

namespace Scripting
{
    class Script;
    class Engine;

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

        State getState() const;

    private:
        typedef boost::shared_ptr<Script> ScriptPtr;
        typedef std::map<std::string, ScriptPtr> ScriptMap;

        friend class ScriptManagerFactory;
        ScriptManager(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager,
                      Utilities::Memory::pool_id pool,
                      const boost::shared_ptr<Utilities::IO::FileSystem>& fileSystem,
                      const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties);

        static const std::string SCRIPT_BASE_PATH;

        std::string startupScriptName;

        const boost::shared_ptr<Utilities::Memory::MemoryManager> memory;
        const Utilities::Memory::pool_id pool;

        boost::shared_ptr<Utilities::IO::FileSystem> fileSystem;
        boost::shared_ptr<Engine> engine;

        ScriptMap scripts;
    };
}

#endif	/* SCRIPTING_SCRIPTMANAGER_H */

