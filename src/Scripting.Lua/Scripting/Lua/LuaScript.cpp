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

        LuaScript::LuaScript(lua_State* state, const Utilities::IO::File::Handle& file, const char* name)
        : state(state), name(name)
        {
            int status = luaL_loadbuffer(state, file->getData(), file->getSize(), name);
            logErrors(status);
            
            lua_setglobal(state, name);
        }

        LuaScript::~LuaScript()
        {
        }
        
        void LuaScript::run()
        {
            lua_getglobal(state, name.c_str());
            int status = lua_pcall(state, 0, 0, 0);

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
