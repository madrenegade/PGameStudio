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
#include "Platform/PlatformManager.h"
#include "Platform/LibraryManager.h"
#include "Platform/Library.h"

using namespace Utilities::Properties;
using namespace Utilities::Memory;
using namespace Platform;

namespace Scripting
{
    
    void ScriptManager::addOptionsTo(const PropertyManager::Ptr& properties)
    {
        po::options_description options("Scripting options");

        options.add_options()
            ("Scripting.engine", po::value<std::string > (), "The scripting engine to use")
            ("Scripting.startup", po::value<std::string>(), "The script to run at startup");

        properties->addOptions(options);
    }

    typedef boost::shared_ptr<ScriptEngine> (*CreateFn)(const MemoryManager::Ptr&);
    
    ScriptManager::ScriptManager(const MemoryManager::Ptr& memoryManager,
                                 const boost::shared_ptr<PlatformManager>& platformManager,
                                 const PropertyManager::Ptr& properties)
    {
        // TODO: dedicated scripting memory pool
        
        std::string engineName("Scripting." + properties->get<std::string>("Scripting.engine"));
        
        // load script engine plugin
        boost::shared_ptr<Library> engineLibrary = platformManager->libraries()->load(engineName.c_str());
        
        CreateFn create = reinterpret_cast<CreateFn> (engineLibrary->getFunction("create"));

        engine = create(memoryManager);
        
        std::string startupScriptName(properties->get<std::string>("Scripting.startup"));
        
    }

    ScriptManager::~ScriptManager()
    {
    }
}
