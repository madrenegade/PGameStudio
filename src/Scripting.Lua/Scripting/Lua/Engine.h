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

#include "Utilities/Memory/typedefs.h"
#include "Utilities/Memory/STLAllocator.h"

#include <string>
#include <boost/shared_ptr.hpp>

namespace Utilities
{
    namespace Memory
    {
        class MemoryManager;
    }
}

namespace Scripting
{
    namespace Lua
    {

        class Engine : public ScriptEngine
        {
        public:
            Engine(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memory,
                   Utilities::Memory::pool_id poolID);

            virtual ~Engine();

            virtual const char* getExtension() const;

            virtual boost::shared_ptr<Script> load(const Utilities::IO::File& file, const char* name);

            virtual boost::shared_ptr<Extractor> createExtractor(AnyVector& params) const;

            virtual Command* getCommand() const;
            virtual void registerFunction(const char* name, Command* cmd, int (*fn)(ScriptEngine*));

            virtual void setReturnValue(const bool& b);
            virtual void setReturnValue(const long& i);
            virtual void setReturnValue(const double& d);
            virtual void setReturnValue(const String& s);

            virtual void setVariable(const char* const name, const bool& value);
            virtual void setVariable(const char* const name, const long& value);
            virtual void setVariable(const char* const name, const double& value);
            virtual void setVariable(const char* const name, const String& value);

        private:
            static const std::string EXTENSION;

            boost::shared_ptr<Utilities::Memory::MemoryManager> memory;
            Utilities::Memory::pool_id pool;

            std::shared_ptr<lua_State> state;

            void logErrors(int status);

            typedef boost::shared_ptr<Wrapper> WrapperPtr;
            std::vector<WrapperPtr, Utilities::Memory::STLAllocator<WrapperPtr> > wrappers;
        };
    }
}


#endif	/* SCRIPTING_LUA_ENGINE_H */

