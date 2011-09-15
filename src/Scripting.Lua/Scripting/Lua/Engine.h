/* 
 * File:   Engine.h
 * Author: madrenegade
 *
 * Created on September 14, 2011, 7:21 PM
 */

#ifndef SCRIPTING_LUA_ENGINE_H
#define	SCRIPTING_LUA_ENGINE_H

#include "Scripting/ScriptEngine.h"
#include <string>

extern "C"
{
#include <lua.h>
}

namespace Scripting
{
    namespace Lua
    {

        class Engine : public ScriptEngine
        {
        public:
            Engine();
            virtual ~Engine();

            virtual const char* getExtension() const;
            
            virtual void runScript(const Utilities::IO::File& file);

        private:
            static const std::string EXTENSION;

            lua_State* state;

            void logErrors(int status);
        };
    }
}


#endif	/* SCRIPTING_LUA_ENGINE_H */

