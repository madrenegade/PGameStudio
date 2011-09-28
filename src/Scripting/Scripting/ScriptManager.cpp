/* 
 * File:   ScriptManager.cpp
 * Author: madrenegade
 * 
 * Created on September 14, 2011, 6:48 PM
 */

#include "Scripting/ScriptManager.h"
#include "Scripting/ScriptEngine.h"
#include "Scripting/Script.h"

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
        MemoryPoolSettings scriptPool(1 * KByte, 1 * KByte, 128 * Byte,
            1 * KByte, 1 * KByte, 256 * Byte,
            1 * KByte, 1 * KByte, 512 * Byte);
        scriptPool.addOptionsTo(properties, "Scripting");

        po::options_description options("Scripting options");

        options.add_options()
            ("Scripting.engine", po::value<std::string > (), "The scripting engine to use")
            ("Scripting.startup", po::value<std::string > (), "The script to run at startup");

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
        std::string engineName("Scripting." + properties->get<std::string > ("Scripting.engine"));

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
        if (scripts.find(name) == scripts.end())
        {
            String filename(SCRIPT_BASE_PATH.c_str(), SCRIPT_BASE_PATH.size());
            filename.append("/");
            filename.append(name);
            filename.append(engine->getExtension());

            File scriptFile = fileSystem->read(filename.c_str());

            ScriptPtr script = engine->load(scriptFile, filename.c_str());
            scripts[name] = script;
        }

        scripts[name]->run();
    }

    void ScriptManager::runScript(const Core::Events::EventID& id, const boost::any& data)
    {
        const char* scriptName = boost::any_cast<const char*>(data);
        runScript(scriptName);
    }

    void ScriptManager::setVariable(const Core::Events::EventID& id, const boost::any& data)
    {
        typedef std::pair<const char*, bool> DataTypeBool;
        typedef std::pair<const char*, long> DataTypeLong;
        typedef std::pair<const char*, double> DataTypeDouble;
        typedef std::pair<const char*, String> DataTypeString;

        if (typeid (DataTypeBool) == data.type())
        {
            const DataTypeBool var = boost::any_cast<DataTypeBool> (data);
            engine->setVariable(var.first, var.second);
        }
        else if (typeid (DataTypeLong) == data.type())
        {
            const DataTypeLong var = boost::any_cast<DataTypeLong> (data);
            engine->setVariable(var.first, var.second);
        }
        else if (typeid (DataTypeDouble) == data.type())
        {
            const DataTypeDouble var = boost::any_cast<DataTypeDouble> (data);
            engine->setVariable(var.first, var.second);
        }
        else if (typeid (DataTypeString) == data.type())
        {
            const DataTypeString var = boost::any_cast<DataTypeString> (data);
            engine->setVariable(var.first, var.second);
        }
        else
        {
            LOG(FATAL) << "setVariable does not support type " << data.type().name();
        }

    }
}
