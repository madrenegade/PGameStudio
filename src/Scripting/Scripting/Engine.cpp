/*
 * File:   Engine.cpp
 * Author: madrenegade
 *
 * Created on September 14, 2011, 7:21 PM
 */

#include "Scripting/Engine.h"
#include "Scripting/Script.h"
#include "Scripting/Allocator.h"

#include "Utilities/IO/File.h"
#include "Utilities/Memory/MemoryManager.h"

#include <lua.hpp>

#include <glog/logging.h>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

namespace Scripting
{
    struct LuaStateDeleter
    {

        void operator()(lua_State* state)
        {
            lua_close(state);
        }
    };

    const std::string Engine::EXTENSION(".lua");

    Engine::Engine(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memory,
                   Utilities::Memory::pool_id poolID)
        : memory(memory), pool(poolID)
    {
        Allocator::memory = memory;
        Allocator::pool = poolID;

        state.reset(lua_newstate(Allocator::allocate, 0), LuaStateDeleter());

        if (!state)
        {
            LOG(FATAL) << "Could not initialize LUA";
        }

        luaL_openlibs(state.get());
    }

    const char* Engine::getExtension() const
    {
        return EXTENSION.c_str();
    }

    State Engine::getState() const
    {
        return state.get();
    }

    boost::shared_ptr<Script> Engine::load(const Utilities::IO::File::Handle& file, const char* const name)
    {
        VLOG(2) << "Loading script " << name;

        boost::shared_ptr<Script> script = memory->construct(Script(state.get(), file, name), pool);

        return script;
    }

    void Engine::runGarbageCollection()
    {
        VLOG_EVERY_N(3, 100) << "LUA mem: " << lua_getgccount(state.get()) << "kB";
        //lua_gc(state.get(), LUA_GCCOLLECT, 0);
    }

    void Engine::setVariable(const char* const name, const bool& value)
    {
        lua_pushboolean(state.get(), value);
        lua_setglobal(state.get(), name);
    }

    void Engine::setVariable(const char* const name, const long& value)
    {
        lua_pushinteger(state.get(), value);
        lua_setglobal(state.get(), name);
    }

    void Engine::setVariable(const char* const name, const double& value)
    {
        lua_pushnumber(state.get(), value);
        lua_setglobal(state.get(), name);
    }

    void Engine::setVariable(const char* const name, const String& value)
    {
        lua_pushstring(state.get(), value.c_str());
        lua_setglobal(state.get(), name);
    }

    void Engine::logErrors(int status)
    {
        if (status != 0)
        {
            LOG(FATAL) << "-- " << lua_tostring(state.get(), -1) << std::endl;
            lua_pop(state.get(), 1); // remove error message
        }
    }
}


