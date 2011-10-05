/*
 * File:   ScriptManager.h
 * Author: madrenegade
 *
 * Created on September 14, 2011, 6:48 PM
 */

#ifndef SCRIPTING_SCRIPTMANAGER_H
#define	SCRIPTING_SCRIPTMANAGER_H


#include <boost/function.hpp>
#include <boost/type_traits.hpp>

#include "Core/Events/typedefs.h"

#include "Scripting/typedefs.h"

#include "Utilities/Memory/typedefs.h"
#include "Utilities/Memory/STLAllocator.h"
#include "Utilities/string.h"

#include <vector>

#include <luabind/luabind.hpp>
#include <luabind/operator.hpp>
using namespace luabind;

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

    class ScriptManager
    {
    public:
        static void addOptionsTo(Utilities::Properties::PropertyManager* const properties);

        void runStartupScript();

        void load(const char* const name);
        void runScript(const char* const name);

        void onSetVariable(const Core::Events::EventID& id, const boost::any& data);
        void setVariable(const char* const name, const bool& value);
        void setVariable(const char* const name, const long& value);
        void setVariable(const char* const name, const double& value);
        void setVariable(const char* const name, const String& value);

        template<typename T>
        void setVariable(const char* const name, const T& value)
        {
            luabind::globals(state.get())[name] = value;
        }

        void runGarbageCollection();

        State getState() const;

    private:
        void logErrors(int status);

        typedef std::shared_ptr<Script> ScriptPtr;
        typedef std::pair<const String, ScriptPtr> ScriptMapEntry;
        typedef Utilities::Memory::STLAllocator<ScriptMapEntry> ScriptMapEntryAllocator;
        typedef std::map<String, ScriptPtr, std::less<String>, ScriptMapEntryAllocator> ScriptMap;

        friend class ScriptManagerFactory;
        ScriptManager(Utilities::Memory::MemoryManager* const memoryManager,
                      Utilities::Memory::pool_id pool,
                      const Utilities::IO::FileSystem* const fileSystem,
                      const Utilities::Properties::PropertyManager* const properties);

        static const std::string SCRIPT_BASE_PATH;

        std::string startupScriptName;

        Utilities::Memory::MemoryManager* const memory;
        const Utilities::Memory::pool_id pool;

        const Utilities::IO::FileSystem* const fileSystem;

        std::shared_ptr<lua_State> state;

        ScriptMap scripts;
    };
}

#endif	/* SCRIPTING_SCRIPTMANAGER_H */

