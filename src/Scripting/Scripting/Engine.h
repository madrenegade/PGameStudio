/*
 * File:   Engine.h
 * Author: madrenegade
 *
 * Created on September 14, 2011, 7:21 PM
 */

#ifndef SCRIPTING_ENGINE_H
#define	SCRIPTING_ENGINE_H

#include "Scripting/typedefs.h"

#include "Utilities/Memory/typedefs.h"
#include "Utilities/Memory/STLAllocator.h"
#include "Utilities/IO/File.h"
#include "Utilities/string.h"

#include <string>
#include <boost/shared_ptr.hpp>

#include <lua.hpp>

namespace Utilities
{
    namespace Memory
    {
        class MemoryManager;
    }
}

namespace Scripting
{
    class Script;

    class Engine
    {
    public:
        Engine(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memory,
               Utilities::Memory::pool_id poolID);

        const char* getExtension() const;

        State getState() const;

        boost::shared_ptr<Script> load(const Utilities::IO::File::Handle& file, const char* const name);

        void runGarbageCollection();

        void setVariable(const char* const name, const bool& value);
        void setVariable(const char* const name, const long& value);
        void setVariable(const char* const name, const double& value);
        void setVariable(const char* const name, const String& value);

    private:
        static const std::string EXTENSION;

        boost::shared_ptr<Utilities::Memory::MemoryManager> memory;
        Utilities::Memory::pool_id pool;

        std::shared_ptr<lua_State> state;

        void logErrors(int status);
    };
}


#endif	/* SCRIPTING_ENGINE_H */

