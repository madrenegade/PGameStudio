/*
 * File:   ScriptManagerFactory.cpp
 * Author: madrenegade
 *
 * Created on September 15, 2011, 4:56 PM
 */

#include "Scripting/ScriptManagerFactory.h"
#include "Scripting/ScriptManager.h"

#include "Utilities/Properties/PropertyManager.h"
#include "Utilities/Memory/MemoryManager.h"



using namespace Utilities::Memory;
using namespace Utilities::Properties;
using namespace Utilities::IO;

namespace Scripting
{

    std::shared_ptr<ScriptManager> ScriptManagerFactory::create(MemoryManager* const memoryManager,
            const FileSystem* const fileSystem,
            const PropertyManager* const properties)
    {
        const std::shared_ptr<Pool> pool = createMemoryPool(properties);

        const pool_id poolID = memoryManager->registerMemoryPool(pool);

        return memoryManager->construct(ScriptManager(memoryManager, poolID, fileSystem, properties), poolID);
    }

    ScriptManagerFactory::ScriptManagerFactory()
    {
    }

    ScriptManagerFactory::~ScriptManagerFactory()
    {
    }

    std::shared_ptr<Pool> ScriptManagerFactory::createMemoryPool(const PropertyManager* const properties)
    {
        size_t soMax = properties->get<size_t > ("Scripting.memory.smallObjects.maxSize");
        size_t soPage = properties->get<size_t > ("Scripting.memory.smallObjects.pageSize");
        size_t soBlock = properties->get<size_t > ("Scripting.memory.smallObjects.blockSize");

        size_t moMax = properties->get<size_t > ("Scripting.memory.mediumObjects.maxSize");
        size_t moPage = properties->get<size_t > ("Scripting.memory.mediumObjects.pageSize");
        size_t moBlock = properties->get<size_t > ("Scripting.memory.mediumObjects.blockSize");

        size_t loMax = properties->get<size_t > ("Scripting.memory.largeObjects.maxSize");
        size_t loPage = properties->get<size_t > ("Scripting.memory.largeObjects.pageSize");
        size_t loBlock = properties->get<size_t > ("Scripting.memory.largeObjects.blockSize");

        MemoryPoolSettings scriptingPoolSettings(
            soMax, soPage, soBlock,
            moMax, moPage, moBlock,
            loMax, loPage, loBlock);

        std::shared_ptr<Pool> pool = Pool::create("ScriptingPool", scriptingPoolSettings);

        return pool;
    }
}
