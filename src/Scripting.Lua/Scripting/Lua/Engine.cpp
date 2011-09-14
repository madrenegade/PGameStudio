/* 
 * File:   Engine.cpp
 * Author: madrenegade
 * 
 * Created on September 14, 2011, 7:21 PM
 */

#include "Scripting/Lua/Engine.h"

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

        Engine::Engine()
        : state(0)
        {
            state = lua_open();

            if (state == 0)
            {
                LOG(FATAL) << "Could not initialize LUA";
            }

            luaL_openlibs(state);
//            int s = luaL_loadfile(state, "scripts/helloworld.lua");
//
//            if (s == 0)
//            {
//                // execute Lua program
//                s = lua_pcall(state, 0, LUA_MULTRET, 0);
//            }
//
//            report_errors(state, s);
        }

        Engine::~Engine()
        {
            // NOTE: close always crashes event for the simplest use case
            // lua_close(state);
            // state = 0;
        }
        
        void Engine::logErrors(int status)
        {
            if (status != 0)
            {
                LOG(FATAL) << "-- " << lua_tostring(L, -1) << std::endl;
                lua_pop(L, 1); // remove error message
            }
        }
    }
}


