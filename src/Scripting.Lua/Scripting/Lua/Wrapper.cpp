/*
 * File:   Wrapper.cpp
 * Author: madrenegade
 *
 * Created on September 15, 2011, 1:44 PM
 */

#include "Scripting/Lua/Wrapper.h"

namespace Scripting
{
    namespace Lua
    {

        Wrapper::Wrapper(ScriptFunction fn, ScriptEngine* const engine)
        : fn(fn), engine(engine)
        {
        }

        int Wrapper::operator()()
        {
            return fn(engine);
        }
    }
}


