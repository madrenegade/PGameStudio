#include "Scripting/Lua/Engine.h"

#include "Utilities/Memory/MemoryManager.h"

extern "C"
{

    boost::shared_ptr<Scripting::ScriptEngine> create(const Utilities::Memory::MemoryManager::Ptr& memory)
    {
        return memory->construct(Scripting::Lua::Engine());
    }
}