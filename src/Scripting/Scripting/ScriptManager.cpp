/*
 * File:   ScriptManager.cpp
 * Author: madrenegade
 *
 * Created on September 14, 2011, 6:48 PM
 */

#include "Scripting/ScriptManager.h"
#include "Scripting/Script.h"
#include "Scripting/Allocator.h"

#include "Utilities/Properties/PropertyManager.h"
#include "Utilities/Memory/MemoryManager.h"
#include "Utilities/IO/FileSystem.h"

using namespace Utilities::Properties;
using namespace Utilities::Memory;
using namespace Utilities::IO;

namespace Scripting
{
    const std::string ScriptManager::SCRIPT_BASE_PATH("scripts");

    void ScriptManager::addOptionsTo(const PropertyManager::Ptr& properties)
    {
        MemoryPoolSettings scriptPool(1 * KByte, 1 * KByte, 128 * Byte,
                                      1 * KByte, 1 * KByte, 256 * Byte,
                                      1 * KByte, 1 * KByte, 512 * Byte);
        scriptPool.addOptionsTo(properties, "Scripting");

        po::options_description options("Scripting options");

        options.add_options()
        ("Scripting.engine", po::value<std::string > (), "The scripting engine to use")
        ("Scripting.startup", po::value<std::string > (), "The script to run at startup");

        properties->addOptions(options);
    }

    ScriptManager::ScriptManager(const MemoryManager::Ptr& memoryManager,
                                 Utilities::Memory::pool_id pool,
                                 const boost::shared_ptr<FileSystem>& fileSystem,
                                 const PropertyManager::Ptr& properties)
        : startupScriptName(properties->get<std::string>("Scripting.startup")),
          memory(memoryManager), pool(pool), fileSystem(fileSystem)
    {
        Allocator::memory = memory;
        Allocator::pool = pool;

        state.reset(lua_newstate(Allocator::allocate, 0), lua_close);

        if (!state)
        {
            LOG(FATAL) << "Could not initialize LUA";
        }

        luaL_openlibs(state.get());

        luabind::open(state.get());
    }

    void ScriptManager::runStartupScript()
    {
        runScript(startupScriptName.c_str());
    }

    void ScriptManager::runScript(const char* const name)
    {
        if (scripts.find(name) == scripts.end())
        {
            VLOG(2) << "Loading script " << name;

            String filename(SCRIPT_BASE_PATH.c_str(), SCRIPT_BASE_PATH.size());
            filename.append("/");
            filename.append(name);
            filename.append(".lua");

            File::Handle scriptFile = fileSystem->read(filename.c_str());

            ScriptPtr script = memory->construct(Script(state.get(), scriptFile, name), pool);
            scripts[name] = script;
        }

        scripts[name]->run();
    }

    void ScriptManager::onSetVariable(const Core::Events::EventID& /*id*/, const boost::any& data)
    {
        typedef std::pair<const char*, bool> DataTypeBool;
        typedef std::pair<const char*, long> DataTypeLong;
        typedef std::pair<const char*, double> DataTypeDouble;
        typedef std::pair<const char*, String> DataTypeString;

        if (typeid (DataTypeBool) == data.type())
        {
            const DataTypeBool var = boost::any_cast<DataTypeBool> (data);
            setVariable(var.first, var.second);
        }
        else if (typeid (DataTypeLong) == data.type())
        {
            const DataTypeLong var = boost::any_cast<DataTypeLong> (data);
            setVariable(var.first, var.second);
        }
        else if (typeid (DataTypeDouble) == data.type())
        {
            const DataTypeDouble var = boost::any_cast<DataTypeDouble> (data);
            setVariable(var.first, var.second);
        }
        else if (typeid (DataTypeString) == data.type())
        {
            const DataTypeString var = boost::any_cast<DataTypeString> (data);
            setVariable(var.first, var.second);
        }
        else
        {
            LOG(FATAL) << "setVariable does not support type " << data.type().name();
        }
    }

    void ScriptManager::setVariable(const char* const name, const bool& value)
    {
        lua_pushboolean(state.get(), value);
        lua_setglobal(state.get(), name);
    }

    void ScriptManager::setVariable(const char* const name, const long& value)
    {
        lua_pushinteger(state.get(), value);
        lua_setglobal(state.get(), name);
    }

    void ScriptManager::setVariable(const char* const name, const double& value)
    {
        lua_pushnumber(state.get(), value);
        lua_setglobal(state.get(), name);
    }

    void ScriptManager::setVariable(const char* const name, const String& value)
    {
        lua_pushstring(state.get(), value.c_str());
        lua_setglobal(state.get(), name);
    }

    void ScriptManager::runGarbageCollection()
    {
//        VLOG_EVERY_N(3, 100) << "LUA mem: " << lua_getgccount(state.get()) << "kB";
//        LOG_EVERY_N(INFO, 100) << lua_gc(state.get(), LUA_GCCOLLECT, 0);
    }

    State ScriptManager::getState() const
    {
        return state.get();
    }

    void ScriptManager::logErrors(int status)
    {
        if (status != 0)
        {
            LOG(FATAL) << "-- " << lua_tostring(state.get(), -1) << std::endl;
            lua_pop(state.get(), 1); // remove error message
        }
    }
}
