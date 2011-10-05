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
        static std::shared_ptr<ScriptManager> create(const std::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager,
                const std::shared_ptr<Utilities::IO::FileSystem>& fileSystem,
                const std::shared_ptr<Utilities::Properties::PropertyManager>& properties);

    private:
        ScriptManagerFactory();
        ~ScriptManagerFactory();

        static std::shared_ptr<Utilities::Memory::Pool> createMemoryPool(const std::shared_ptr<Utilities::Properties::PropertyManager>& properties);
    };
}

#endif	/* SCRIPTING_SCRIPTMANAGERFACTORY_H */

