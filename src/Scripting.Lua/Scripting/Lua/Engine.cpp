/* 
 * File:   Engine.cpp
 * Author: madrenegade
 * 
 * Created on September 14, 2011, 7:21 PM
 */

#include "Scripting/Lua/Engine.h"
#include "Utilities/IO/File.h"

extern "C"
{
#include <lualib.h>
}

#include <luabind/luabind.hpp>
#include <glog/logging.h>

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
        
        void Engine::runScript(const Utilities::IO::File& file)
        {
            int status = luaL_loadbuffer(state, file.getData(), file.getSize(), "LUA_SCRIPT");
            
            if(status == 0)
            {
                status = lua_pcall(state, 0, LUA_MULTRET, 0);
            }
            
            logErrors(status);
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


