/*
 * File:   Wrapper.h
 * Author: madrenegade
 *
 * Created on September 15, 2011, 1:44 PM
 */

#ifndef SCRIPTING_LUA_WRAPPER_H
#define	SCRIPTING_LUA_WRAPPER_H

extern "C"
{
#include <lua.h>
}

namespace Scripting
{
    class ScriptEngine;

    namespace Lua
    {
        typedef int (*ScriptFunction)(ScriptEngine*);

        class Wrapper
        {
        public:
            Wrapper(ScriptFunction fn, ScriptEngine* const engine);

            int operator()();

        private:
            ScriptFunction fn;
            ScriptEngine* const engine;
        };
    }
}


#endif	/* SCRIPTING_LUA_WRAPPER_H */

