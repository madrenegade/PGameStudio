/* 
 * File:   Engine.h
 * Author: madrenegade
 *
 * Created on September 14, 2011, 7:21 PM
 */

#ifndef SCRIPTING_LUA_ENGINE_H
#define	SCRIPTING_LUA_ENGINE_H

#include "Scripting/ScriptEngine.h"
#include "Scripting/typedefs.h"
#include "Scripting/Lua/Wrapper.h"
#include <string>

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

            virtual void runScript(const Utilities::IO::File& file, const char* name);

            virtual boost::shared_ptr<Extractor> createExtractor(AnyVector& params) const;

            virtual Command* getCommand() const;
            virtual void registerFunction(const char* name, Command* cmd, int (*fn)(ScriptEngine*));

            virtual void setReturnValue(const bool& b);
            virtual void setReturnValue(const long& i);
            virtual void setReturnValue(const double& d);

            virtual void setReturnValue(const std::string& s);

        private:
            static const std::string EXTENSION;

            lua_State* state;

            void logErrors(int status);

            std::vector<boost::shared_ptr<Wrapper> > wrappers;
        };
    }
}


#endif	/* SCRIPTING_LUA_ENGINE_H */

