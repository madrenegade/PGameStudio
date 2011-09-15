/* 
 * File:   Engine.cpp
 * Author: madrenegade
 * 
 * Created on September 14, 2011, 7:21 PM
 */

#include "Scripting/Lua/Engine.h"
#include "Scripting/Lua/Extractor.h"
#include "Utilities/IO/File.h"

extern "C"
{
#include <lualib.h>
}

#include <luabind/luabind.hpp>
#include <glog/logging.h>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

namespace Scripting
{
    namespace Lua
    {

        const std::string Engine::EXTENSION(".lua");

        Engine::Engine()
        : state(0)
        {
            state = lua_open();

            if (state == 0)
            {
                LOG(FATAL) << "Could not initialize LUA";
            }

            luaL_openlibs(state);
        }

        Engine::~Engine()
        {
            // NOTE: close always crashes event for the simplest use case
            // lua_close(state);
        }

        const char* Engine::getExtension() const
        {
            return EXTENSION.c_str();
        }

        void Engine::runScript(const Utilities::IO::File& file, const char* name)
        {
            int status = luaL_loadbuffer(state, file.getData(), file.getSize(), name);

            if (status == 0)
            {
                status = lua_pcall(state, 0, LUA_MULTRET, 0);
            }

            logErrors(status);
        }

        boost::shared_ptr<Scripting::Extractor> Engine::createExtractor(AnyVector& params) const
        {
            boost::shared_ptr<Scripting::Extractor> extractor(new Lua::Extractor(params, state));
            return extractor;
        }
        
        Command* Engine::getCommand() const
        {
            return reinterpret_cast<Command*>(lua_tointeger(state, lua_upvalueindex(1)));
        }
        
        static int wrapperFunction(lua_State* state)
        {
            Wrapper* wrapper = reinterpret_cast<Wrapper*>(lua_tointeger(state, lua_upvalueindex(2)));
            
            return (*wrapper)();
        }
        
        void Engine::registerFunction(const char* name, Command* cmd, int (*fn)(ScriptEngine*))
        {
            boost::shared_ptr<Wrapper> wrapper(new Wrapper(fn, this));
            wrappers.push_back(wrapper);
            
            lua_pushinteger(state, reinterpret_cast<long>(cmd));
            lua_pushinteger(state, reinterpret_cast<long>(wrapper.get()));
            
            lua_pushcclosure(state, wrapperFunction, 2);
            
            lua_setglobal(state, name);
        }
        
        void Engine::setReturnValue(const bool& b)
        {
            lua_pushboolean(state, b ? 1 : 0);
        }
        
        void Engine::setReturnValue(const long& i)
        {
            lua_pushinteger(state, i);
        }
        
        void Engine::setReturnValue(const double& d)
        {
            lua_pushnumber(state, d);
        }

        void Engine::setReturnValue(const std::string& s)
        {
            lua_pushlstring(state, s.c_str(), s.length());
        }

        void Engine::logErrors(int status)
        {
            if (status != 0)
            {
                LOG(FATAL) << "-- " << lua_tostring(state, -1) << std::endl;
                lua_pop(state, 1); // remove error message
            }
        }
    }
}


