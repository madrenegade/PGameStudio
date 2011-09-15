/* 
 * File:   ScriptManager.cpp
 * Author: madrenegade
 * 
 * Created on September 14, 2011, 6:48 PM
 */

#include "Scripting/ScriptManager.h"
#include "Scripting/ScriptEngine.h"

#include "Utilities/Properties/PropertyManager.h"
#include "Utilities/Memory/MemoryManager.h"
#include "Utilities/IO/FileSystem.h"

#include "Platform/PlatformManager.h"
#include "Platform/LibraryManager.h"
#include "Platform/Library.h"

using namespace Utilities::Properties;
using namespace Utilities::Memory;
using namespace Utilities::IO;
using namespace Platform;

namespace Scripting
{
    const std::string ScriptManager::SCRIPT_BASE_PATH("scripts");

    void ScriptManager::addOptionsTo(const PropertyManager::Ptr& properties)
    {
        po::options_description options("Scripting options");

        options.add_options()
            ("Scripting.engine", po::value<std::string > (), "The scripting engine to use")
            ("Scripting.startup", po::value<std::string > (), "The script to run at startup")

            ("Scripting.memory.smallObjects.maxSize", po::value<size_t > ()->default_value(1 * KByte), "Maximum size for the small object area in the Scripting memory pool")
            ("Scripting.memory.smallObjects.pageSize", po::value<size_t > ()->default_value(1 * KByte), "Page size for the small object area in the Scripting memory pool")
            ("Scripting.memory.smallObjects.blockSize", po::value<size_t > ()->default_value(128 * Byte), "Block size for the small object area in the Scripting memory pool")

            ("Scripting.memory.mediumObjects.maxSize", po::value<size_t > ()->default_value(1 * KByte), "Maximum size for the medium object area in the Scripting memory pool")
            ("Scripting.memory.mediumObjects.pageSize", po::value<size_t > ()->default_value(1 * KByte), "Page size for the medium object area in the Scripting memory pool")
            ("Scripting.memory.mediumObjects.blockSize", po::value<size_t > ()->default_value(128 * Byte), "Block size for the medium object area in the Scripting memory pool")

            ("Scripting.memory.largeObjects.maxSize", po::value<size_t > ()->default_value(1 * KByte), "Maximum size for the large object area in the Scripting memory pool")
            ("Scripting.memory.largeObjects.pageSize", po::value<size_t > ()->default_value(1 * KByte), "Page size for the large object area in the Scripting memory pool")
            ("Scripting.memory.largeObjects.blockSize", po::value<size_t > ()->default_value(128 * Byte), "Block size for the large object area in the Scripting memory pool");

        properties->addOptions(options);
    }

    typedef boost::shared_ptr<ScriptEngine> (*CreateFn)(const MemoryManager::Ptr&, pool_id pool);

    ScriptManager::ScriptManager(const MemoryManager::Ptr& memoryManager,
                                 Utilities::Memory::pool_id pool,
                                 const boost::shared_ptr<PlatformManager>& platformManager,
                                 const boost::shared_ptr<FileSystem>& fileSystem,
                                 const PropertyManager::Ptr& properties)
    : startupScriptName(properties->get<std::string>("Scripting.startup")),
    memory(memoryManager), fileSystem(fileSystem)
    {
        // TODO: dedicated scripting memory pool

        std::string engineName("Scripting." + properties->get<std::string > ("Scripting.engine"));

        // load script engine plugin
        boost::shared_ptr<Library> engineLibrary = platformManager->libraries()->load(engineName.c_str());

        CreateFn create = reinterpret_cast<CreateFn> (engineLibrary->getFunction("create"));

        engine = create(memoryManager, pool);
    }

    ScriptManager::~ScriptManager()
    {
    }

    void ScriptManager::runStartupScript()
    {
        runScript(startupScriptName.c_str());
    }

    void ScriptManager::runScript(const char* name)
    {
        std::string filename(SCRIPT_BASE_PATH + "/" + name + engine->getExtension());

        File scriptFile = fileSystem->read(filename.c_str());

        engine->runScript(scriptFile, filename.c_str());
    }
}
