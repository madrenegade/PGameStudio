/*
 * File:   ScriptManagerFactory.h
 * Author: madrenegade
 *
 * Created on September 15, 2011, 4:56 PM
 */

#ifndef SCRIPTING_SCRIPTMANAGERFACTORY_H
#define	SCRIPTING_SCRIPTMANAGERFACTORY_H

#include <memory>

namespace Utilities
{
    namespace Memory
    {
        class Pool;
        class MemoryManager;
    }

    namespace Properties
    {
        class PropertyManager;
    }

    namespace IO
    {
        class FileSystem;
    }
}

namespace Scripting
{
    class ScriptManager;

    class ScriptManagerFactory
    {
    public:
        static std::shared_ptr<ScriptManager> create(Utilities::Memory::MemoryManager* const memoryManager,
                const Utilities::IO::FileSystem* const fileSystem,
                const Utilities::Properties::PropertyManager* const properties);

    private:
        ScriptManagerFactory();
        ~ScriptManagerFactory();

        static std::shared_ptr<Utilities::Memory::Pool> createMemoryPool(const Utilities::Properties::PropertyManager* const properties);
    };
}

#endif	/* SCRIPTING_SCRIPTMANAGERFACTORY_H */

