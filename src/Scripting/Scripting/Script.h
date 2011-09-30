/*
 * File:   LuaScript.h
 * Author: madrenegade
 *
 * Created on September 27, 2011, 1:08 PM
 */

#ifndef SCRIPTING_LUASCRIPT_H
#define	SCRIPTING_LUASCRIPT_H

#include "Scripting/Script.h"
#include "Utilities/IO/File.h"
#include "Utilities/string.h"

#include <lua.hpp>

namespace Scripting
{
    class Script
    {
    public:
        Script(lua_State* const state, const Utilities::IO::File::Handle& file, const char* const name);

        void run();

    private:
        void logErrors(int status);

        lua_State* const state;
        String name;
    };
}

#endif	/* SCRIPTING_SCRIPT_H */

