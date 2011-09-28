/* 
 * File:   Engine.cpp
 * Author: madrenegade
 * 
 * Created on September 14, 2011, 7:21 PM
 */

#include "Scripting/Lua/Engine.h"
#include "Scripting/Lua/Extractor.h"
#include "Scripting/Lua/LuaScript.h"

#include "Utilities/IO/File.h"
#include "Utilities/Memory/MemoryManager.h"

#include <lua.hpp>

#include <glog/logging.h>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

namespace Scripting
{
    namespace Lua
    {

        struct LuaStateDeleter
        {

            void operator()(lua_State * state)
            {
                lua_close(state);
            }
        };

        const std::string Engine::EXTENSION(".lua");

        Engine::Engine(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memory,
                       Utilities::Memory::pool_id poolID)
        : memory(memory), pool(poolID)
        {
            state.reset(lua_open(), LuaStateDeleter());

            if (!state)
            {
                LOG(FATAL) << "Could not initialize LUA";
            }

            luaL_openlibs(state.get());

            lua_newtable(state.get());
            lua_setglobal(state.get(), "var");
        }

        Engine::~Engine()
        {
        }

        const char* Engine::getExtension() const
        {
            return EXTENSION.c_str();
        }

        boost::shared_ptr<Script> Engine::load(const Utilities::IO::File& file, const char* name)
        {
            VLOG(2) << "Loading script " << name;

            boost::shared_ptr<Script> script = memory->construct(LuaScript(state.get(), file, name), pool);

            return script;
        }

        boost::shared_ptr<Scripting::Extractor> Engine::createExtractor(AnyVector& params) const
        {
            boost::shared_ptr<Scripting::Extractor> extractor = memory->construct(Lua::Extractor(params, state.get()), pool);
            return extractor;
        }

        Command* Engine::getCommand() const
        {
            return reinterpret_cast<Command*> (lua_tointeger(state.get(), lua_upvalueindex(1)));
        }

        static int wrapperFunction(lua_State* state)
        {
            Wrapper* wrapper = reinterpret_cast<Wrapper*> (lua_tointeger(state, lua_upvalueindex(2)));

            return (*wrapper)();
        }

        void Engine::registerFunction(const char* name, Command* cmd, int (*fn)(ScriptEngine*))
        {
            boost::shared_ptr<Wrapper> wrapper = memory->construct(Wrapper(fn, this), pool);
            wrappers.push_back(wrapper);

            lua_pushinteger(state.get(), reinterpret_cast<long> (cmd));
            lua_pushinteger(state.get(), reinterpret_cast<long> (wrapper.get()));

            lua_pushcclosure(state.get(), wrapperFunction, 2);

            lua_setglobal(state.get(), name);
        }

        void Engine::setReturnValue(const bool& b)
        {
            lua_pushboolean(state.get(), b ? 1 : 0);
        }

        void Engine::setReturnValue(const long& i)
        {
            lua_pushinteger(state.get(), i);
        }

        void Engine::setReturnValue(const double& d)
        {
            lua_pushnumber(state.get(), d);
        }

        void Engine::setReturnValue(const String& s)
        {
            lua_pushlstring(state.get(), s.c_str(), s.length());
        }

        void Engine::setVariable(const char* const name, const bool& value)
        {
            lua_getglobal(state.get(), "var");
            lua_pushstring(state.get(), name);
            lua_pushboolean(state.get(), value);
            lua_settable(state.get(), -3);
        }

        void Engine::setVariable(const char* const name, const long& value)
        {
            lua_getglobal(state.get(), "var");
            lua_pushstring(state.get(), name);
            lua_pushinteger(state.get(), value);
            lua_settable(state.get(), -3);
        }

        void Engine::setVariable(const char* const name, const double& value)
        {
            lua_getglobal(state.get(), "var");
            lua_pushstring(state.get(), name);
            lua_pushnumber(state.get(), value);
            lua_settable(state.get(), -3);
        }

        void Engine::setVariable(const char* const name, const String& value)
        {
            lua_getglobal(state.get(), "var");
            lua_pushstring(state.get(), name);
            lua_pushstring(state.get(), value.c_str());
            lua_settable(state.get(), -3);
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
}


