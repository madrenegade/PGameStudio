/*
 * File:   Command.cpp
 * Author: madrenegade
 *
 * Created on September 15, 2011, 12:13 PM
 */

#include "Scripting/Command.h"

namespace Scripting
{
    void setReturnValue(lua_State* const state, const bool& b)
    {
        lua_pushboolean(state, b ? 1 : 0);
    }

    void setReturnValue(lua_State* const state, const long& i)
    {
        lua_pushinteger(state, i);
    }

    void setReturnValue(lua_State* const state, const double& d)
    {
        lua_pushnumber(state, d);
    }

    void setReturnValue(lua_State* const state, const String& s)
    {
        lua_pushlstring(state, s.c_str(), s.length());
    }

    Command::Command(const char* const name)
        : name(name)
    {

    }
}
