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
            LuaScript(lua_State* const state, const Utilities::IO::File::Handle& file, const char* const name);
            virtual ~LuaScript();

            virtual void run();

        private:
            void logErrors(int status);

            lua_State* const state;
            String name;
        };
    }
}

#endif	/* SCRIPTING_LUA_LUASCRIPT_H */

