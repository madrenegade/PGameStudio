/* 
 * File:   SystemScene.cpp
 * Author: madrenegade
 * 
 * Created on September 27, 2011, 2:00 PM
 */

#include "Scripting/SystemScene.h"
#include "Scripting/ExecutorTask.h"
#include "Utilities/Properties/PropertyManager.h"

namespace Scripting
{
    const std::string SystemScene::EXTENSION("scripting");
    
    SystemScene::SystemScene()
    {
    }

    SystemScene::~SystemScene()
    {
    }

    void SystemScene::addOptionsTo(const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties) const
    {
        
    }

    const char* const SystemScene::getSceneFileExtension() const
    {
        return EXTENSION.c_str();
    }

    void SystemScene::load(const Utilities::IO::File& file)
    {
        
    }

    void SystemScene::initialize()
    {
        scriptManager = properties->get<ScriptManager*>("SCRIPT_MANAGER");
    }

    tbb::task* SystemScene::getTask(tbb::task* parent)
    {
        return new(parent->allocate_child()) ExecutorTask(scriptManager);
    }
}
