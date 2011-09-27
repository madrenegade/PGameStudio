/* 
 * File:   LuaScript.h
 * Author: madrenegade
 *
 * Created on September 27, 2011, 1:08 PM
 */

#ifndef SCRIPTING_LUA_LUASCRIPT_H
#define	SCRIPTING_LUA_LUASCRIPT_H

#include "Scripting/Script.h"
#include "Utilities/IO/File.h"
#include "Utilities/string.h"

#include <lua.hpp>

namespace Scripting
{
    namespace Lua
    {

        class LuaScript : public Scripting::Script
        {
        public:
            LuaScript(lua_State* state, const Utilities::IO::File& file, const char* name);
            virtual ~LuaScript();
            
            virtual void run();
            
        private:
            void logErrors(int status);
            
            lua_State* state;
            
            Utilities::IO::File file;
            String name;
        };
    }
}

#endif	/* SCRIPTING_LUA_LUASCRIPT_H */

