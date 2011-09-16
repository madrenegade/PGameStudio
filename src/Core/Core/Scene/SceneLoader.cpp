/* 
 * File:   SceneLoader.cpp
 * Author: madrenegade
 * 
 * Created on September 16, 2011, 1:23 PM
 */

#include "Core/Scene/SceneLoader.h"
#include "Core/Scene/Scene.h"
#include "Core/Scene/SystemScene.h"

#include "Utilities/Memory/STLAllocator.h"

#include "Platform/PlatformManager.h"
#include "Platform/Library.h"

#include <glog/logging.h>

using namespace Utilities::Memory;

namespace Core
{

    SceneLoader::SceneLoader()
    {
        
    }
    
    SceneLoader::SceneLoader(const boost::shared_ptr<Utilities::IO::FileSystem>& fileSystem,
                             const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager,
                             const boost::shared_ptr<Platform::PlatformManager>& platform)
    : fileSystem(fileSystem), memoryManager(memoryManager), platform(platform)
    {
    }

    SceneLoader::~SceneLoader()
    {
    }

    boost::shared_ptr<Scene> SceneLoader::loadScene(const char* name)
    {
        LOG(INFO) << "Loading scene " << name;
        
        SystemVector neededSystems;
        neededSystems.push_back("Graphics");
        
        boost::shared_ptr<Scene> scene = memoryManager->construct(Scene());
        
        loadSystemLibraries(neededSystems, scene.get());
        
        return scene;
    }
    
    typedef boost::shared_ptr<SystemScene> (*CreateFn)(const MemoryManager::Ptr&, pool_id pool);
    
    void SceneLoader::loadSystemLibraries(const SystemVector& systems, Scene* scene)
    {
        for(auto i = systems.begin(); i != systems.end(); ++i)
        {
            boost::shared_ptr<Platform::Library> lib = platform->libraries()->load(i->c_str());
            
            CreateFn create = reinterpret_cast<CreateFn> (lib->getFunction("createSystemScene"));
            
            // TODO: seperate pools for each system
            boost::shared_ptr<SystemScene> systemScene = create(memoryManager, 0);
            systemScene->setMemoryManager(memoryManager);
            systemScene->setPlatformManager(platform);
            
            scene->addSystemScene(systemScene);
        }
    }
}
