/* 
 * File:   LuaScript.cpp
 * Author: madrenegade
 * 
 * Created on September 27, 2011, 1:08 PM
 */

#include "Scripting/Lua/LuaScript.h"

#include <glog/logging.h>

namespace Scripting
{
    namespace Lua
    {

        LuaScript::LuaScript(lua_State* state, const Utilities::IO::File& file, const char* name)
        : state(state), file(file), name(name)
        {
        }

        LuaScript::~LuaScript()
        {
        }
        
        void LuaScript::run()
        {
            int status = luaL_loadbuffer(state, file.getData(), file.getSize(), name.c_str());

            if (status == 0)
            {
                status = lua_pcall(state, 0, LUA_MULTRET, 0);
            }

            logErrors(status);
        }
        
        void LuaScript::logErrors(int status)
        {
            if (status != 0)
            {
                LOG(FATAL) << "-- " << lua_tostring(state, -1) << std::endl;
                lua_pop(state, 1); // remove error message
            }
        }
    }
}
